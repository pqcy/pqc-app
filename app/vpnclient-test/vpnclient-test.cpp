#include <iostream>
#include "vpnclient.h"
#include <libnet.h>

using namespace std;

void usage()
{
    printf("syntax: vpnclient <dummy interface name> <real interface name> <server ip> <server port>\n");
    printf("vpnclient dum0 wlan0 10.1.1.2 12345\n");
}

struct Param
{
    char *dumDev_;
    char *realDev_;
    string ip_;
    int port_;
} param;


bool parse(Param *param, int argc, char *argv[])
{
    if (argc != 5)
    {
        usage();
        return false;
    }
    param->dumDev_ = argv[1];
    param->realDev_ = argv[2];
    //param->ip_ = Ip(argv[3]);
    param->port_ = atoi(argv[4]);
    return true;
}

int main(int argc, char *argv[])
{
    VpnClient vc;

    if (!parse(&param, argc, argv))
           return -1;

    bool ok = vc.open(param.dumDev_, Ip(inet_addr(argv[3])), param.port_);
    if(!ok){
        printf("vc.open return false %s\n", vc.error_.data());
        return -1;
    }

    while(true) {

        std::string s;
        std::getline(std::cin, s);
        if( s == "q" ) break;

    }
    vc.close();
}
