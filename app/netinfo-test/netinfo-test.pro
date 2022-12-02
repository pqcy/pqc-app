TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH = ../../src
SOURCES += \
        ../../src/ip.cpp \
        ../../src/mac.cpp \
        ../../src/netinfo.cpp \
        netinfo-test.cpp

HEADERS += \
    ../../src/ip.h \
    ../../src/mac.h \
    ../../src/netinfo.h
