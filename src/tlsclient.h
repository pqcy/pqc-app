#pragma once

#include "client.h"
#include "tcpclient.h"
#include "tlssession.h"

struct TlsClient : public Client, public TlsSession {
	TcpClient tcpClient_;
    STACK_OF(OPENSSL_STRING) *ssl_args_ = NULL; //groups flag, kem alg id
    SSL_CONF_CTX *cctx_{nullptr};
    SSL_CTX *ctx_{nullptr};
    char* groups_ = NULL;
    char* alg_ = NULL;

    bool connect(Ip ip, int port) override;
};
