#include "vpnserver.h"

void VpnServer::run(Session* session) {

    std::puts("connected\n");

    char buf[4096] = {0,};
    int size = 4096;
    ClientInfo clnt;
    clnt.pcapDevice_.open(dev_, size, 1, 1000);

    int res = session->read(buf, size);
    if (res == -1) {
        printf("read error!\n");
        return;
    }
    clnt.pcapDevice_.write((u_char *)buf, size);

    std::puts("closed\n");
    clnt.pcapDevice_.close();

}
