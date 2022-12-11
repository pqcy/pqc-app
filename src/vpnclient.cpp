#include "vpnclient.h"

bool VpnClient::open(const char *dev, Ip ip, int port) {
    if (!tcpClient_.connect(ip, port)){
        error_ = tcpClient_.error_;
        return false;
    }
    if (!pcapDevice_.open(dev, BUFSIZ, 1, 10)){
        error_ = pcapDevice_.error_;
        return false;
    }
    if (!rawSocket_.open())
    {    error_ = rawSocket_.error_;

        return false;
    }
    captureAndWriteThread_ = new std::thread (&VpnClient::captureAndWrite, this);
    readAndSendMethread_ = new std::thread (&VpnClient::readAndSendMe, this);

    return true;
}

bool VpnClient::close() {
    tcpClient_.close();
    pcapDevice_.close();
    rawSocket_.close();

    captureAndWriteThread_->join();
    delete captureAndWriteThread_;

    readAndSendMethread_->join();
    delete readAndSendMethread_;
    return true;
}

void VpnClient::captureAndWrite() { // pcap

    struct pcap_pkthdr *header;
    const u_char *data;

    while (true) {
       if (pcapDevice_.read(&header, &data) == -1)
           break;
       if (tcpClient_.write((char*)data, header->caplen) == -1)
           break;
    }
}

void VpnClient::readAndSendMe() { // raw socket

    char *buf = NULL;
    int size;

    while (true) {
        size = tcpClient_.read(buf, 4096);
        if (size < 0)
            break;
        if (!rawSocket_.write(buf, sizeof(buf)))
            break;
    }
}
