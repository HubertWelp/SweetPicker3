TARGET = SP3Bildanalysator

CONFIG += qt
CONFIG += c++11

QT       += core
QT += network
QT += widgets

SOURCES += \
        main.cpp \
    kamera.cpp \
    orientierungsermittler.cpp \
    ressourcen.cpp \
    verwalter.cpp \
    udpnode.cpp \
    textauswerter.cpp

HEADERS += \
    kamera.h \
    orientierungsermittler.h \
    verwalter.h \
    ressourcen.h \
    udpnode.hpp \
    textauswerter.h


INCLUDEPATH += /usr/local/opencv/include/opencv4

LIBS += -L/usr/local/opencv/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_videoio

LIBS += /home/Student/git/SP3/SweetPicker3/build-SP3Admin-Desktop_Qt_5_12_3_GCC_64bit-Debug/konfig.o

