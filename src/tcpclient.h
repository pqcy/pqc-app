#pragma once

#include "client.h"
#include "ip.h"
#include "tcpsession.h"

struct TcpClient : public Client, public TcpSession {
    bool connect(Ip ip, int port) override;
};
