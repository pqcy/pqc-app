#pragma once

#include "client.h"
#include "tcpsession.h"

struct TcpClient : public Client, public TcpSession {
	bool connect(std::string host, int port) override;
};
