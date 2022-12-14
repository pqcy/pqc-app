TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
DESTDIR=../../bin
SOURCES += \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        ../../src/tlsserver.cpp \
        ../../src/tlssession.cpp \
        tlsserver-test.cpp

HEADERS += \
	../../src/server.h \
	../../src/session.h \
	../../src/tcpserver.h \
	../../src/tcpsession.h \
	../../src/tlsserver.h \
	../../src/tlssession.h

#shared objects linking
LIBS += -L$$PWD/../../lib/ -lssl -lcrypto

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
