TARGET = SP3Bildanalysator

CONFIG += qt
CONFIG += c++11

QT       += core
QT += network
QT += widgets

SOURCES += \
        main.cpp \
    kamera.cpp \
    verwalter.cpp \
    udpnode.cpp

HEADERS += \
    kamera.h \
    verwalter.h \
    ressourcen.h \
    udpnode.hpp

INCLUDEPATH += /usr/local/include/opencv4/

LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_videoio

