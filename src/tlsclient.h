#pragma once

#include "tcpclient.h"
#include "tlssession.h"

struct TlsClient : public TcpClient, public TlsSession {
    SSL_CTX *ctx_;

    TlsClient();
    bool connect(std::string host, int port) override;
};
