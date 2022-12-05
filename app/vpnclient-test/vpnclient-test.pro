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
        ../../src/tcpclient.cpp \
        ../../src/tcpsession.cpp \
        ../../src/vpnclient.cpp \
        ../../src/ip.cpp \
        vpnclient-test.cpp

HEADERS += \
        ../../src/pcapdevice.h \
        ../../src/rawsocket.h \
        ../../src/client.h \
        ../../src/session.h \
        ../../src/tcpclient.h \
        ../../src/tcpsession.h \
        ../../src/ip.h \
        ../../src/vpnclient.h
