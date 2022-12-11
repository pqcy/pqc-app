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

#libssl.a
unix:!macx: LIBS += -L$$PWD/../../lib/ -lssl

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib/libssl.a

#libcrypto.a
unix:!macx: LIBS += -L$$PWD/../../lib/ -lcrypto

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../lib/libcrypto.a

#liboqs.a
unix:!macx: LIBS += -L$$PWD/../../oqs/lib/ -loqs

INCLUDEPATH += $$PWD/../../oqs/include
DEPENDPATH += $$PWD/../../oqs/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../oqs/lib/liboqs.a
