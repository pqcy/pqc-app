#include "tlsclient.h"

TlsClient::TlsClient() {

}

bool TlsClient::connect(std::string host, int port) {
    if (TcpClient::connect(host, port))
        return false;


    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */

    const SSL_METHOD *method = TLSv1_2_client_method();
    ctx_ = SSL_CTX_new(method);
    assert(ctx_ != nullptr);

    ssl_ = SSL_new(ctx_);
    assert(ssl_ != nullptr);

    SSL_set_fd(ssl_, sock_);

}
