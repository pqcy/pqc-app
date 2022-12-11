TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src \
               ../../include \
               ../../oqs/include
DESTDIR=../../bin
SOURCES += \
        ../../src/ip.cpp \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        tcpserver-test.cpp

HEADERS += \
        ../../src/ip.h \
	../../src/server.h \
	../../src/session.h \
	../../src/tcpserver.h \
	../../src/tcpsession.h
