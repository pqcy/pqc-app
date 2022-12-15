#pragma once

#include <QThread>
#include "tlsclient.h"

class RThread : public QThread, TlsClient
{
    Q_OBJECT
public:
    RThread();
    TlsClient* tc;

private:
    void run();
signals:
    void readMsg(char* msg);
};

