TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
DESTDIR=../../bin
LIBS+=-lpcap
SOURCES += \
        ../../src/pcapdecice.cpp\
        ../../src/rawsocket.cpp\
        ../../src/ip.cpp\
        ../../src/tcpclient.cpp \
        ../../src/tcpsession.cpp \
        ../../src/vpnclient.cpp\
        vpnclient-test.cpp

HEADERS += \
        ../../src/pcapdevice.h \
        ../../src/rawsocket.h \
        ../../src/ip.h\
        ../../src/client.h \
        ../../src/session.h \
        ../../src/tcpclient.h \
        ../../src/tcpsession.h \
        ../../src/vpnclient.h
