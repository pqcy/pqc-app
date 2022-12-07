#include "vpnserver.h"

bool VpnServer::dhcp(Session* session, ClientInfo client) {

    char buf[4096] = {0,};
    int size = 4096;
    int readSize = session->read(buf, size);

    if (readSize == -1) {
        error_ = strerror(errno);
        return false;
    }
    int res = client.pcapDevice_.write((u_char *)buf, readSize);
    if (res == -1) {
        error_ = client.pcapDevice_.error_;
        return false;
    }

    return true;
}

void VpnServer::run(Session* session) {


    ClientInfo client;

    client.pcapDevice_.open(dev_, 4096, 1, 1000);

    std::puts("connect\n");

    if (!dhcp(session, client)) {
        printf("dhcp error!!\n%s\n", error_.data());
        return;
    }

    client.pcapDevice_.close();
    std::puts("closed\n");

}
