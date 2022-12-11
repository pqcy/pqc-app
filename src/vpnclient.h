#pragma once

#include <cstdio>
#include "tcpclient.h"
#include "pcapdevice.h"
#include "rawsocket.h"
#include <thread>

struct VpnClient {
    std::string error_;
    TcpClient tcpClient_;
    PcapDevice pcapDevice_;
    RawSocket rawSocket_;
    std::thread* captureAndWriteThread_{nullptr};
    std::thread* readAndSendMethread_{nullptr};

    bool open(const char *dev, Ip ip, int port);
    bool close();

    void captureAndWrite();
    void readAndSendMe();
};
