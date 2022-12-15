QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../../src
DESTDIR=../../bin

SOURCES += \
    ../../src/tcpclient.cpp \
    ../../src/tcpsession.cpp \
    ../../src/tlsclient.cpp \
    ../../src/tlssession.cpp \
    main.cpp \
    pqcchat.cpp \
    rthread.cpp

HEADERS += \
    ../../src/client.h \
    ../../src/session.h \
    ../../src/tcpclient.h \
    ../../src/tcpsession.h \
    ../../src/tlsclient.h \
    ../../src/tlssession.h \
    pqcchat.h \
    rthread.h

FORMS += \
    pqcchat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#shared objects linking
LIBS += -L$$PWD/../../lib/ -lssl -lcrypto

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

