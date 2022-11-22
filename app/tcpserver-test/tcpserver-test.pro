TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
SOURCES += \
        ../../src/tcpserver.cpp \
        ../../src/tcpsession.cpp \
        tcpserver-test.cpp

HEADERS += \
	../../src/server.h \
	../../src/session.h \
	../../src/tcpserver.h \
	../../src/tcpsession.h
