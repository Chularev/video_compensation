TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        block.cpp \
        filereader.cpp \
        filewriter.cpp \
        frame.cpp \
        frameinfo.cpp \
        main.cpp \
        pixel.cpp

HEADERS += \
    block.h \
    filereader.h \
    filewriter.h \
    frame.h \
    frameinfo.h \
    pixel.h
