TARGET = SP3Bildanalysator

CONFIG += c++11
CONFIG += console c++11

SOURCES += \
        main.cpp \
    kamera.cpp

HEADERS += \
    kamera.h

INCLUDEPATH += /usr/local/include/opencv4/

LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_videoio

