TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
DESTDIR=../../bin
SOURCES += \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        ../../src/vpnserver.cpp\
        vpnserver-test.cpp

HEADERS += \
        ../../src/server.h \
        ../../src/session.h \
        ../../src/tcpserver.h \
        ../../src/tcpserver.h \
        ../../src/vpnserver.h
