#pragma once

#include "client.h"
#include "tcpclient.h"
#include "tlssession.h"

struct TlsClient : public Client, public TlsSession {
    TcpClient tcpClient_;
    SSL_CTX *ctx_{nullptr};
    static int config_ctx(SSL_CTX *ctx);

    bool connect(Ip ip, int port) override;
};
