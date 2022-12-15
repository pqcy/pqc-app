#pragma once

#include <QWidget>
#include <iostream>
#include <netinet/in.h>
#include "rthread.h"
#include "tlsclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PqcChat; }
QT_END_NAMESPACE

class PqcChat : public QWidget
{
    Q_OBJECT

public:
    PqcChat(QWidget *parent = nullptr);
    ~PqcChat();
    TlsClient tc;
    std::string name_;
private slots:
    void on_btnConn_clicked();
    void on_btnSend_clicked();
    void on_btnClose_clicked();
    void showMsg(char*msg);

private:
    Ui::PqcChat *ui;
    RThread* rthread;
};



