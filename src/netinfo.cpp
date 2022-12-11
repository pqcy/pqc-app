#include "netinfo.h"

bool NetInfo::init(std::string intfName) {
    // mac_ ip_ setting
    int sock_;
    struct ifreq ifr;

    memset(&ifr, 0x00, sizeof(ifr));
    strcpy(ifr.ifr_name, intfName.data());

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    ioctl(sock_, SIOCGIFHWADDR, &ifr); // mac

    mac_ = reinterpret_cast<uint8_t*>(ifr.ifr_hwaddr.sa_data);

    ioctl(sock_, SIOCGIFADDR, &ifr); // ip
    struct sockaddr_in *sin = (sockaddr_in*)&ifr.ifr_addr;
    ip_ = ntohl(sin->sin_addr.s_addr);

    return true;
}
