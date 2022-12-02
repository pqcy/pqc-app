#pragma once

#include <string>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

struct RawSocket {
    int sock_;
    std::string error_;

    bool open();
    bool close();
    bool bind(char* dev);
    int read(char* buf, int size);
    int write(char* buf, int size);
};
