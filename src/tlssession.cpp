#include "tlssession.h"

TlsSession::TlsSession(int sock, SSL* ssl) {
    sock_ = sock;
    ssl_ = ssl;
}

int TlsSession::read(char* buf, int size) {
    return ::SSL_read(ssl_, buf, size);
}

int TlsSession::write(char* buf, int size) {
    return ::SSL_write(ssl_, buf, size);
}

bool TlsSession::close() {
    ::SSL_free(ssl_);
    ::shutdown(sock_, SHUT_RDWR);
    ::close(sock_);

    return true;
}
