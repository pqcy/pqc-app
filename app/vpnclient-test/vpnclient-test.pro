TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
DESTDIR=../../bin
SOURCES += \
        ../../src/tcpclient.cpp \
        ../../src/tcpsession.cpp \
        ../../src/vpnclient.cpp\
        vpnclient-test.cpp

HEADERS += \
        ../../src/client.h \
        ../../src/session.h \
        ../../src/tcpclient.h \
        ../../src/tcpsession.h \
        ../../src/vpnclient.h
