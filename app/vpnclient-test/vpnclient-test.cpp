#include "vpnclient.h"
#include <libnet.h>

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
        port_ = std::stoi(argv[4]);
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
    Param param;

    if (!param.parse(argc, argv)){
        Param::usage();
        return -1;
    }
    VpnClient vc;

    vc.open(param.dumDev_, param.ip_, param.port_);

    struct pcap_pkthdr* header;
    const u_char* packet;

    //char buf[1000] = {0,};

    vc.captureAndWrite(header, packet, 1000);

    while(true){
        struct libnet_ethernet_hdr *p = (struct libnet_ethernet_hdr*)packet;
        struct libnet_ipv4_hdr * p2 = (struct libnet_ipv4_hdr*)(packet+ 14);

        printf("src mac: %02x:%02x:%02x:%02x:%02x:%02x\n",p->ether_shost[0],p->ether_shost[1],p->ether_shost[2],p->ether_shost[3],p->ether_shost[4],p->ether_shost[5]);
        printf("des mac : %02x:%02x:%02x:%02x:%02x:%02x\n",p->ether_dhost[0],p->ether_dhost[1],p->ether_dhost[2],p->ether_dhost[3],p->ether_dhost[4],p->ether_dhost[5]);

        if(ntohs(p->ether_type) == 0x0800){
            printf("ip source address : %u.%u.%u.%u\n", p2->ip_src.s_addr &0xff, (p2->ip_src.s_addr >> 8 ) &0xff, (p2->ip_src.s_addr >> 16 ) &0xff, (p2->ip_src.s_addr>>24) &0xff); //s_addr 4바이트 변수 & little endian
            printf("ip destination adress : %u.%u.%u.%u\n", p2->ip_dst.s_addr & 0xff, (p2->ip_dst.s_addr >> 8) & 0xff, (p2->ip_dst.s_addr >> 16)&0xff, (p2->ip_dst.s_addr >> 24)&0xff);
        }
        else{
            printf("None ip\n");
        }
    }

    vc.close();
}
