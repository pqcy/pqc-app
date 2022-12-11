#include "pcapdevice.h"


bool PcapDevice::open(const char *device, int snaplen, int promisc, int to_ms) {

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_ = pcap_open_live(device, snaplen, promisc, to_ms, errbuf);
    if(pcap_ == nullptr){
        error_ = errbuf; // 알아서 바꿔서 넣어줌
        return false;
    }
    return true;

}
bool PcapDevice::close() {
    pcap_close(pcap_);
    pcap_ = nullptr;
    return true;
}

int PcapDevice::read(struct pcap_pkthdr **pkt_header,const u_char **pkt_data) {
    int res = pcap_next_ex(pcap_, pkt_header, pkt_data);
    
    if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
        error_ = pcap_geterr(pcap_);
        return -1;
	}
    
    return (*pkt_header)->caplen;
}

int PcapDevice::write(const u_char *buf, int size){
    int res = pcap_sendpacket(pcap_, buf, size);

    if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
        error_ = pcap_geterr(pcap_);
        return -1;
	}
    return size;
}
