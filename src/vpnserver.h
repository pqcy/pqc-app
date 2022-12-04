#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <map>

#include "tcpserver.h"
#include "pcapdevice.h"
#include "ip.h"
#include "mac.h"

struct VpnServer : TcpServer {
    struct ClientInfo {
        PcapDevice pcapDevice_;
        Mac mac_;
        Ip ip_;
    };

    struct ClientInfoMap : std::map<Mac, ClientInfo> {
    } cim_;

    void run(Session* session) override;
};
