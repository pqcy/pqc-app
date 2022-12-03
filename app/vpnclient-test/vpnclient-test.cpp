#include "vpnclient.h"

void usage()
{
    printf("syntax: vpnclient <dummy interface name> <real interface name> <server ip> <server port>\n");
    printf("vpnclient dum0 wlan0 10.1.1.2 12345\n");
}

typedef struct
{
    char *dumDev_;
    char *realDev_;
} Param;

Param param = {
    .dumDev_ = NULL,
    .realDev_ = NULL
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
    return true;
}

int main(int argc, char *argv[])
{
    if (!parse(&param, argc, argv))
        return -1;

    VpnClient vc;
}
