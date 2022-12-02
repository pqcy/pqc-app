#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "mac.h"
#include "ip.h"

struct NetInfo {
    bool init(std::string intfName); // like ens33 -> interface
    Mac mac_;
    Ip ip_;
};
