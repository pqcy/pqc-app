#include "pqcchat.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PqcChat w;
    w.show();
    return a.exec();
}
