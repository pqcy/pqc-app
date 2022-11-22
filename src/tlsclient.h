#pragma once

#include "client.h"
#include "tcpclient.h"
#include "tlssession.h"

struct TlsClient : public Client, public TlsSession {
	TcpClient tcpClient_;
	SSL_CTX *ctx_{nullptr};

	bool connect(std::string host, int port) override;
};
