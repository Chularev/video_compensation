TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS +=-msse3
QMAKE_CXXFLAGS +=-msse4.1

SOURCES += \
        block.cpp \
        filereader.cpp \
        filewriter.cpp \
        frame.cpp \
        frameinfo.cpp \
        main.cpp \
        motionvector.cpp \
        pixel.cpp \
        videocompensation.cpp

HEADERS += \
    block.h \
    filereader.h \
    filewriter.h \
    frame.h \
    frameinfo.h \
    motionvector.h \
    pixel.h \
    videocompensation.h
