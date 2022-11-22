TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += ../../src
SOURCES += \
	../../src/tcpclient.cpp \
	../../src/tcpsession.cpp \
	tcpclient-test.cpp

HEADERS += \
	../../src/client.h \
	../../src/session.h \
	../../src/tcpclient.h \
	../../src/tcpsession.h
