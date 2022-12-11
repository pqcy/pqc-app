TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH = ../../src
SOURCES += \
    ../../src/rawsocket.cpp\
    rawsocket-test.cpp
