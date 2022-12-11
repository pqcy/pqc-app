#pragma once //헤더파일을 여러번 불러올때 문제가 생겨서 써줌

#include <iostream>
#include <string>
#include <pcap.h>


class PcapDevice{

public:
    std::string error_;
     // pcap 그때그때 사용하게 초기화, pcap_t* pcap를 숨긴다, 즉 open,close,write,read에 pcap_t* pcap 인자로 줄 필요가 없다 공부 더 필요
    pcap_t* pcap_{nullptr};
    
    bool open(const char *device, int snaplen, int promisc, int to_ms);
    bool close();
    int read(struct pcap_pkthdr **pkt_header,const u_char **pkt_data);
    int write(const u_char *buf, int size);
};
