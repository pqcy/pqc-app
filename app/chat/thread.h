#pragma once

#include <QThread>
#include "pqcchat.h"
#include "session.h"

class Thread : public QThread
{
public:
    Thread();
    void readAndPrint(Ui::PqcChat *ui, Session* session);
};

