#include "rawsocket.h"


bool RawSocket::open() {
    sock_ = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock_ < 0) {
        error_ = strerror(errno);
        return false;
    }
    return true;
}
bool RawSocket::close() {
    ::close(sock_);
    return true;
}
bool RawSocket::bind(char* dev) {
    int res = ::setsockopt(sock_, SOL_SOCKET, SO_BINDTODEVICE, dev, sizeof(dev));
    if (res < 0) {
        error_ = strerror(errno);
        return false;
    }

    return true;
}
int RawSocket::read(char*buf, int size) {
     int res = ::read(sock_, buf, size);
     if (res < 0) {
         error_ = strerror(errno);
         return false;
     }
     return true;
}
int RawSocket::write(char* buf, int size) {
    struct sockaddr_in addr;
     addr.sin_family = AF_INET;
    int res = ::sendto(sock_, buf, size, 0,
                       (const struct sockaddr *)&addr, sizeof(addr));
    if (res < 0) {
        error_ = strerror(errno);
        return false;
    }
    return true;
}

