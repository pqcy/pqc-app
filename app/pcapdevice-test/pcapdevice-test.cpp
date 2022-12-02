#include <iostream>
#include "pcapdevice.h"


struct Param {

    std::string intfName_;
    bool parse(int argc, char **argv) {
        if (argc != 2)
            return false;
        intfName_ = argv[1];
        return true;
    }

    static void usage() {
        printf("syntax : pcapdevice-test <interface name>\n");
        printf("sample : pcapdevice-test wlan0\n");
    }
};
 struct libnet_ethernet_hdr
 {
     u_int8_t  ether_dhost[6];/* destination ethernet address */
     u_int8_t  ether_shost[6];/* source ethernet address */
     u_int16_t ether_type;                 /* protocol */
 };

 struct libnet_ipv4_hdr
 {
 #if (LIBNET_LIL_ENDIAN)
     u_int8_t ip_hl:4,      /* header length */
            ip_v:4;         /* version */
 #endif
 #if (LIBNET_BIG_ENDIAN)
     u_int8_t ip_v:4,       /* version */
            ip_hl:4;        /* header length */
 #endif
     u_int8_t ip_tos;       /* type of service */
 #ifndef IPTOS_LOWDELAY
 #define IPTOS_LOWDELAY      0x10
 #endif
 #ifndef IPTOS_THROUGHPUT
 #define IPTOS_THROUGHPUT    0x08
 #endif
 #ifndef IPTOS_RELIABILITY
 #define IPTOS_RELIABILITY   0x04
 #endif
 #ifndef IPTOS_LOWCOST
 #define IPTOS_LOWCOST       0x02
 #endif
     u_int16_t ip_len;         /* total length */
     u_int16_t ip_id;          /* identification */
     u_int16_t ip_off;
 #ifndef IP_RF
 #define IP_RF 0x8000        /* reserved fragment flag */
 #endif
 #ifndef IP_DF
 #define IP_DF 0x4000        /* dont fragment flag */
 #endif
 #ifndef IP_MF
 #define IP_MF 0x2000        /* more fragments flag */
 #endif
 #ifndef IP_OFFMASK
 #define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
 #endif
     u_int8_t ip_ttl;          /* time to live */
     u_int8_t ip_p;            /* protocol */
     u_int16_t ip_sum;         /* checksum */
     struct in_addr ip_src, ip_dst; /* source and dest address */
 };

int main(int argc, char *argv[])
{
    Param param;
    if (!param.parse(argc, argv)) {
        Param::usage();
        return -1;
    }

    PcapDevice pcapDevice;
    bool wh = pcapDevice.open(argv[1]/*param.intfName_*/, BUFSIZ, 1, 1000);
    if(!wh){
        printf("opne error\n");
        return -1;
    }
    while(true){


        struct pcap_pkthdr* header;
        const u_char* packet;
        int wh2 = pcapDevice.read(&header, &packet);
        if(wh2 == -1){
            printf("read error\n");
            return -2;
        }
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
    pcapDevice.close();
    return 0;
}
