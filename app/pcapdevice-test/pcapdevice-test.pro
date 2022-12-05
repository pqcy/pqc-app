TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH = ../../src
LIBS+=-lpcap
SOURCES += \
    ../../src/pcapdevice.cpp\
    pcapdevice-test.cpp
