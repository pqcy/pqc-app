TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
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

#shared objects linking
LIBS += -L$$PWD/../../lib/ -lssl -lcrypto

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
