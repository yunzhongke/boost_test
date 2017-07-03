TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
    thread.cpp \
    file.cpp

INCLUDEPATH += -I/home/yunzhongke/work/boostlibrary/include
LIBS += -L/home/yunzhongke/work/boostlibrary/lib -lboost_regex -lboost_system -lboost_filesystem -lboost_thread -lboost_chrono


