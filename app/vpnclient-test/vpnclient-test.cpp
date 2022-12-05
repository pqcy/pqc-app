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
    if (!parse(&param, argc, argv))
        return -1;

    VpnClient vc;
}
