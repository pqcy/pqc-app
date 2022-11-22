TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
LIBS += -lssl -lcrypto
DESTDIR=../../bin
SOURCES += \
        ../../src/tcpclient.cpp \
        ../../src/tcpsession.cpp \
        ../../src/tlsclient.cpp \
        ../../src/tlssession.cpp \
        tlsclient-test.cpp

HEADERS += \
	../../src/client.h \
	../../src/session.h \
        ../../src/tcpclient.h \
        ../../src/tcpsession.h \
        ../../src/tlsclient.h \
        ../../src/tlssession.h
