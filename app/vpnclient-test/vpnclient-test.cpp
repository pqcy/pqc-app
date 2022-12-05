#include <iostream>
#include "vpnclient.h"

using namespace std;

void usage()
{
    printf("syntax: vpnclient <dummy interface name> <real interface name> <server ip> <server port>\n");
    printf("vpnclient dum0 wlan0 10.1.1.2 12345\n");
}

typedef struct
{
    char *dumDev_;
    char *realDev_;
    string ip_;
    int port_;
} Param;

Param param = {
    .dumDev_ = NULL,
    .realDev_ = NULL,
    .ip_ = NULL,
    .port_ = 0
};

bool parse(Param *param, int argc, char *argv[])
{
    if (argc != 5)
    {
        usage();
        return false;
    }
    param->dumDev_ = argv[1];
    param->realDev_ = argv[2];
    param->ip_ = Ip(inet_addr(argv[3]));
    param->port_ = atoi(argv[4]);
    return true;
}

int main(int argc, char *argv[]) {
    VpnClient vc;

    if (!parse(&param, argc, argv))
        return -1;

    if(!vc.open(param.dumDev_, param.ip_, param.port_)) {
        cerr << vc.tcpClient_.error_ << endl;
        return -1;
    }

    struct pcap_pkthdr* header = 0;
    const u_char* packet = 0;

    vc.captureAndWrite(header, packet, 1500);

    vc.close();
}
