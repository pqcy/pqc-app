TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH = ../../src
LIBS+=-lpcap
SOURCES += \
    ../../src/pcapdecice.cpp\
    pcapdevice-test.cpp
