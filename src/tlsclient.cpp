#include "tlsclient.h"

int config_ctx(SSL_CONF_CTX *cctx, STACK_OF(OPENSSL_STRING) *str,
               SSL_CTX *ctx)
{
    int i;

    SSL_CONF_CTX_set_ssl_ctx(cctx, ctx);
    for (i = 0; i < sk_OPENSSL_STRING_num(str); i += 2) {
        const char *flag = sk_OPENSSL_STRING_value(str, i);
        const char *arg = sk_OPENSSL_STRING_value(str, i + 1);
        SSL_CONF_cmd(cctx, flag, arg);
      /*
        if (SSL_CONF_cmd(cctx, flag, arg) <= 0) {
            if (arg != NULL)
                BIO_printf(bio_err, "Error with command: \"%s %s\"\n",
                           flag, arg);
            else
                BIO_printf(bio_err, "Error with command: \"%s\"\n", flag);
            ERR_print_errors(bio_err);
            return 0;
        }
      */
    }
    SSL_CONF_CTX_finish(cctx);
    /*
    if (!SSL_CONF_CTX_finish(cctx)) {
        BIO_puts(bio_err, "Error finishing context\n");
        ERR_print_errors(bio_err);
        return 0;
    }
    */
    return 1;
}

void set_ssl_algs(char* groups, char* alg){
    char groupsBuf[8] = "-groups";
    char algBuf[9] = "kyber512";
    memcpy(groups, groupsBuf, sizeof(groupsBuf));
    memcpy(alg, algBuf, sizeof(algBuf));
}

bool TlsClient::connect(Ip ip, int port) {
    if (!tcpClient_.connect(ip, port)) {
		error_ = tcpClient_.error_;
		return false;
	}
    set_ssl_algs(groups_, alg_);
    /*for SSL_CONF_CTX flag set*/
    if (ssl_args_ == NULL || !sk_OPENSSL_STRING_push(ssl_args_, groups_) || !sk_OPENSSL_STRING_push(ssl_args_, alg_)){
       printf("ssl_args setting fail");
       goto end;
    }
    end:
       sk_OPENSSL_STRING_free(ssl_args_);
       return false;

	OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */
	SSL_load_error_strings(); /* Bring in and register error messages */

	const SSL_METHOD *method = TLS_client_method();
	ctx_ = SSL_CTX_new(method);
	assert(ctx_ != nullptr);

	sock_ = tcpClient_.sock_;
    config_ctx(cctx_, ssl_args_, ctx_); //call config_ctx() -> setting flag and kyber512's nid
    /*
     * if(config_ctx(cctx_, ssl_args_, ctx_) <= 0){
		char buf[256];
        sprintf(buf, "config_ctx() error | tlsclient.cpp line: 62");
		error_ = buf;
		return false;
        }
    */

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
