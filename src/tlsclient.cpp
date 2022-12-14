#include "tlsclient.h"

int TlsClient::config_ctx(SSL_CONF_CTX *cctx, STACK_OF(OPENSSL_STRING) *str, SSL_CTX *ctx){
    int i;
    SSL_CONF_CTX_set_ssl_ctx(cctx, ctx);

    for (i = 0; i < sk_OPENSSL_STRING_num(str); i += 2) {
        const char *flag = sk_OPENSSL_STRING_value(str, i);
        const char *arg = sk_OPENSSL_STRING_value(str, i + 1);
        if(SSL_CONF_cmd(cctx, flag, arg) <= 0){
            if(arg != NULL){
                printf("[Algorithms Set] flag: \"%s\", Algorithm name: \"%s\"\n", flag, arg);
                printf("[NOTICE] Did you export LD_LIBRARY_PATH=pqc-app/lib \?\n");
                printf("[NOTICE] Please Check a Directory name is pqc-app/lib\n");
            }
            else{
                printf("[Error] Fail to set a PQC_Algorithm.\n");
            }
            printf("[NOTICE] Current TLS is no PQC\n");
            return 1;
        }
    }
    if(!SSL_CONF_CTX_finish(cctx)){
        printf("[Error] Can't finishing context\n");
        return 0;
    }
    return 1;
}

bool TlsClient::connect(Ip ip, int port) {
    OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */
    SSL_load_error_strings(); /* Bring in and register error messages */
    STACK_OF(OPENSSL_STRING) *ssl_args = nullptr; //groups flag, kem alg id
    std::string groups = "-groups"; //groups flag
    std::string alg = "kyber512";   //PQC Algorithm name

    if (!tcpClient_.connect(ip, port)) {
        error_ = tcpClient_.error_;
        return false;
    }
    const SSL_METHOD *method = TLS_client_method();
    SSL_CONF_CTX *cctx{nullptr};
    cctx = SSL_CONF_CTX_new();
    ctx_ = SSL_CTX_new(method);
    SSL_CONF_CTX_set_flags(cctx, SSL_CONF_FLAG_CLIENT | SSL_CONF_FLAG_CMDLINE);
    assert(ctx_ != nullptr);

    sock_ = tcpClient_.sock_;

    /*for SSL_CONF_CTX flag set*/
    if (ssl_args == NULL){
        ssl_args = sk_OPENSSL_STRING_new_null();
    }
    if (ssl_args == NULL || !sk_OPENSSL_STRING_push(ssl_args, groups.data()) || !sk_OPENSSL_STRING_push(ssl_args, alg.data())){
       printf("[Error] Memory allcotated\nPlease try again.\n");
       return false;
    }

    /*PQC Algorithms Set*/
    if(config_ctx(cctx, ssl_args, ctx_) <= 0){
        printf("[Error] fail to TLS set\n");
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
