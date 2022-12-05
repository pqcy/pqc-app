#include "vpnclient.h"

struct Param {
    char *dumDev_;
    char *realDev_;
    Ip ip_;
    int port_;

    bool parse(int argc, char** argv) {
        if (argc != 5) return false;

        dumDev_ = argv[1];
        realDev_ = argv[2];
        ip_ = inet_addr(argv[3]);
        port_ = std::stoi(argv[1]);
        return true;
    }

    static void usage()
    {
        printf("syntax: vpnclient <dummy interface name> <real interface name> <server ip> <server port>\n");
        printf("vpnclient dum0 wlan0 10.1.1.2 12345\n");
    }
};

int main(int argc, char *argv[])
{
    VpnClient vc;

    Param param;
    if (!param.parse(argc, argv)) {
        Param::usage();
        return -1;
    }

    if (!vc.tcpClient_.connect(param.ip_, param.port_)) {
        printf("%s\n", vc.tcpClient_.error_.data());
        return -1;
    }
//    struct pcap_pkthdr *header;
//    const u_char *data;
//    char *buf;
//    int size = 4096;

//    vc.captureAndWriteThread_(&VpnClient::captureAndWrite, header, data, size);
//    vc.readAndSendMethread_(vc.readAndSendMe);

    vc.tcpClient_.close();
}
