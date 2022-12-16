#include "pqcchat.h"
#include "ui_pqcchat.h"

PqcChat::PqcChat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PqcChat)
{
    ui->setupUi(this);
    rthread = new RThread();
    connect(rthread, SIGNAL(readMsg(char*)), this, SLOT(showMsg(char*)));
    ui->btnClose->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

PqcChat::~PqcChat()
{
    delete ui;
}

void PqcChat::showMsg(char* msg) {
    ui->textChat->append(msg);
}

void PqcChat::on_btnConn_clicked() {
    std::string ip;
    int port;
    ip = ui->ip->text().toStdString();
    port = ui->port->text().toInt();
    if (port <= 0) {
            ui->textChat->append("포트 번호를 다시 입력해주세요.");
            return;
        }
    printf("%d\n", port);
    name_ = ui->name->text().toStdString();
    if (name_ == "") {
        ui->textChat->append("이름을 입력해주세요.");
        return;
    }

    if (!tc.connect(inet_addr(ip.data()), port) ) {
        std::cerr << tc.error_ << std::endl;
        ui->textChat->append("연결 실패");
        return;
    }
    ui->textChat->append("서버 연결");
    rthread->tc = &tc;
    rthread->start();

    ui->btnConn->setEnabled(false);
    ui->btnClose->setEnabled(true);
    ui->btnSend->setEnabled(true);
    ui->ip->setEnabled(false);
    ui->port->setEnabled(false);
    ui->name->setEnabled(false);
}

void PqcChat::on_btnClose_clicked() {
    rthread->terminate();
    tc.close();
    ui->textChat->append("연결 종료");

    ui->btnConn->setEnabled(true);
    ui->btnClose->setEnabled(false);
    ui->btnSend->setEnabled(false);
    ui->ip->setEnabled(true);
    ui->port->setEnabled(true);
    ui->name->setEnabled(true);
}

void PqcChat::on_btnSend_clicked() {
    QString msg;
    msg = ui->msg->text();
    ui->msg->setText("");
    std::string res = name_ + " : " + msg.toStdString();
    int writeLen = tc.write(res.data(), res.size());

    if (writeLen != -1 ) {
        ui->textChat->append(res.data());
    }
}

