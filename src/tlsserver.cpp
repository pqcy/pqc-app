#include "tlsserver.h"
#include <cstring>
#include <mutex>
#include <openssl/provider.h>

int TlsServer::load_oqs_provider() {
    OSSL_PROVIDER *oqsprov = OSSL_PROVIDER_load(nullptr, "oqsprovider");
    if (oqsprov == nullptr) {
        printf("[Error] Failed to load oqsprovider\n");
        return 0;
    }
    printf("[INFO] oqsprovider loaded successfully\n");
    return 1;
}

bool TlsServer::start(int port) {
    //check_env_path(); //환경변수 예외처리 함수
    if (!load_oqs_provider()) {
        printf("[Error] Failed to load oqsprovider. Ensure that oqsprovider is correctly installed and configured.\n");
        return false;
    }

    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    const SSL_METHOD *method = TLS_server_method();  /* create new server-method instance */
    ctx_ = SSL_CTX_new(method);   /* create new context from method */
    if ( ctx_ == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    // TLS 1.3을 강제 설정
    SSL_CTX_set_min_proto_version(ctx_, TLS1_3_VERSION);
    SSL_CTX_set_max_proto_version(ctx_, TLS1_3_VERSION);

	SSL_CTX_set_security_level(ctx_, 0); //SSL_CTX_set_security_level 함수로 보안 레벨을 낮추어 해당 키를 허용

    if ( SSL_CTX_use_certificate_file(ctx_, pemFileName_.data(), SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        printf("\n[NOTICE] Check a export LD_LIBRARY_PATH=pqc-app/lib\n");
        printf("[NOTICE] Check a name is pqc-app/lib\n");
        abort();
    }
    if ( SSL_CTX_use_PrivateKey_file(ctx_, pemFileName_.data(), SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    if ( !SSL_CTX_check_private_key(ctx_) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }

	acceptSock_ = ::socket(AF_INET, SOCK_STREAM, 0);
	if (acceptSock_ == -1) {
		error_ = strerror(errno);
		return false;
	}

	int res;
#ifdef __linux__
	int optval = 1;
	res = ::setsockopt(acceptSock_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (res == -1) {
		error_ = strerror(errno);
		return false;
	}
#endif // __linux
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	ssize_t res2 = ::bind(acceptSock_, (struct sockaddr *)&addr, sizeof(addr));
	if (res2 == -1) {
		error_ = strerror(errno);
		return false;
	}

	res = listen(acceptSock_, 5);
	if (res == -1) {
		error_ = strerror(errno);
		return false;
	}

    acceptThread_ = new std::thread(&TlsServer::acceptRun, this);
	return true;
}

bool TlsServer::stop() {
	::shutdown(acceptSock_, SHUT_RDWR);
	::close(acceptSock_);
    ::SSL_CTX_free(ctx_);
	if (acceptThread_ != nullptr) {
		delete acceptThread_;
		acceptThread_ = nullptr;
	}

	sessions_.lock();
    for (TlsSession* session: sessions_)
		session->close();
	sessions_.unlock();

	while (true) {
		sessions_.lock();
		bool exit = sessions_.size() == 0;
		sessions_.unlock();
		if (exit) break;
		usleep(1000);
	}

	return true;
}

void TlsServer::acceptRun() {
	while (true) {
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		int newSock = ::accept(acceptSock_, (struct sockaddr *)&addr, &len);
		if (newSock == -1) {
			error_ = strerror(errno);
			break;
        }
        SSL* ssl = SSL_new(ctx_);
        SSL_set_fd(ssl, newSock);
        if ( SSL_accept(ssl) == -1 )  {
             ERR_print_errors_fp(stderr);
             break;
        }
        TlsSession* session = new TlsSession(newSock, ssl);
        std::thread* thread = new std::thread(&TlsServer::_run, this, session);
		thread->detach();
	}
}

void TlsServer::_run(TlsSession* session) {
	sessions_.lock();
	sessions_.push_back(session);
	sessions_.unlock();

	run(session);

	sessions_.lock();
	sessions_.remove(session);
	sessions_.unlock();
}
