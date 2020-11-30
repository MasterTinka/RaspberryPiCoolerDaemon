TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpigpio -lrt -lpthread

SOURCES += \
        main.cpp
