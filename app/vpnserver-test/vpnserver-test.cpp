#include "vpnserver.h"

struct Param {
    int port_;
    char* dev_;

    bool parse(int argc, char** argv) {
        if (argc != 3) return false;
        port_ = std::stoi(argv[1]);
        dev_ = argv[2];
        return true;
    }

    static void usage() {
        printf("syntax: vpnserver <port> <interface name>\n");
        printf("vpnserver 12345 eth0");
    }
};

int main(int argc, char *argv[])
{
    VpnServer vs;

    Param param;
    if (!param.parse(argc, argv)) {
        Param::usage();
        return -1;
    }
    vs.dev_ = param.dev_;

    if (!vs.start(param.port_)) {
        printf("%s\n", vs.error_.data());
        return -1;
    }

    while (true) {
        std::string s;
        std::getline(std::cin, s);
        if (s == "q") break;
    }
    vs.stop();
}
