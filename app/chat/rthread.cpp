#include "rthread.h"

RThread::RThread()
{

}
void RThread::run() {
    while (true) {
        char buf[256];
        int res = tc->read(buf, 512);
        if (res <= 0) break;
        buf[res] = '\0';
        emit readMsg(buf);
    }
}
