#include "vpnclient.h"

bool VpnClient::open(const char *dev, Ip ip, int port) {
    if (!tcpClient_.connect(ip, port))
        return false;
    if (!pcapDevice_.open(dev, BUFSIZ, 1, 10))
        return false;
    if (!rawSocket_.open())
        return false;
    return true;
}

bool VpnClient::close() {
    tcpClient_.close();
    pcapDevice_.close();
    rawSocket_.close();
    //thread close
    return true;
}

void VpnClient::captureAndWrite(struct pcap_pkthdr *header, const u_char *data, int size) { // pcap
    while (true) {
       if (!pcapDevice_.read(&header, &data))
           continue;
       if (!pcapDevice_.write(data, size))
           continue;
    }
}

void VpnClient::readAndSendMe(char *buf, int size) { // raw socket

    while (true) {
        if (!rawSocket_.read(buf, size))
            continue;
        if (!rawSocket_.write(buf, size))
            continue;
    }
}
