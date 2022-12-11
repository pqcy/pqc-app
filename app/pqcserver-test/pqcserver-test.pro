TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src \
               ../../include \
               ../../oqs/include
LIBS += -lssl -lcrypto
DESTDIR=../../bin
SOURCES += \
        ../../src/pqcserver.cpp \
        ../../src/pqcsession.cpp \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        ../../src/tlsserver.cpp \
        ../../src/tlssession.cpp \
        tlsserver-test.cpp

HEADERS += \
	../../src/pqcserver.h \
	../../src/pqcsession.h \
	../../src/server.h \
	../../src/session.h \
	../../src/tcpserver.h \
	../../src/tcpsession.h \
	../../src/tlsserver.h \
	../../src/tlssession.h
