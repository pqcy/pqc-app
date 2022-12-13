TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
LIBS += -L../../lib/libssl.a \
        -L../../lib/libcrypto.a \
        -L../../oqs/lib/liboqs.a
DESTDIR=../../bin
SOURCES += \
        ../../src/pqcclient.cpp \
        ../../src/pqcsession.cpp \
        ../../src/tcpclient.cpp \
        ../../src/tcpsession.cpp \
        ../../src/tlsclient.cpp \
        ../../src/tlssession.cpp \
        tlsclient-test.cpp

HEADERS += \
	../../src/client.h \
    ../../src/pqcclient.h \
    ../../src/pqcsession.h \
	../../src/session.h \
        ../../src/tcpclient.h \
        ../../src/tcpsession.h \
        ../../src/tlsclient.h \
        ../../src/tlssession.h
