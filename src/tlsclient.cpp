#include "tlsclient.h"

bool TlsClient::connect(Ip ip, int port) {
    if (!tcpClient_.connect(ip, port)) {
		error_ = tcpClient_.error_;
		return false;
	}

	OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */
	SSL_load_error_strings(); /* Bring in and register error messages */

	const SSL_METHOD *method = TLS_client_method();
	ctx_ = SSL_CTX_new(method);
	assert(ctx_ != nullptr);

	sock_ = tcpClient_.sock_;
	if(SSL_CTX_set1_groups_list(ctx_, "kyber512") <= 0){ /*kyber512 groups set*/
		char buf[256];
		sprintf(buf, "SSL_CTX_set1_groups_list() error");
		error_ = buf;
		return false;
	}
	ssl_ = SSL_new(ctx_);
	assert(ssl_ != nullptr);

	SSL_set_fd(ssl_, sock_);

	int res = SSL_connect(ssl_);
	if (res <= 0) {
		char buf[256];
		int error_res = SSL_get_error(ssl_, res);
		sprintf(buf, "SSL_connect return %d SSL_get_error=%d", res, error_res);
		error_ = buf;
		return false;
	}

	return true;
}
