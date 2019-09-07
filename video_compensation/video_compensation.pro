TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        filereader.cpp \
        filewriter.cpp \
        frame.cpp \
        frameinfo.cpp \
        main.cpp \
        pixel.cpp

HEADERS += \
    filereader.h \
    filewriter.h \
    frame.h \
    frameinfo.h \
    pixel.h
