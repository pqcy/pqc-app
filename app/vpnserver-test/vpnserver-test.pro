TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
DESTDIR=../../bin
LIBS += -lpcap
SOURCES += \
        ../../src/pcapdevice.cpp \
        ../../src/rawsocket.cpp \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        ../../src/vpnserver.cpp \
        vpnserver-test.cpp

HEADERS += \
        ../../src/pcapdevice.h \
        ../../src/rawsocket.h \
        ../../src/server.h \
        ../../src/session.h \
        ../../src/tcpserver.h \
        ../../src/tcpsession.h \
        ../../src/vpnserver.h
