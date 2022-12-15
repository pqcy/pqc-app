#include "thread.h"

Thread::Thread()
{

}

void Thread::readAndPrint(Ui::PqcChat *ui, Session* session) {
    std::puts("connected");
    char buf[256];
    while (true) {
        int res = session->read(buf, 256);
        ui->textChat->append(buf);;
        if (res <= 0) break;
        buf[res] = '\0';
        std::puts(buf);
    }
    std::puts("disconnected");
    exit(0);

}
