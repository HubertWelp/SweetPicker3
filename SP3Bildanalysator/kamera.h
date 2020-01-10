#ifndef KAMERA_H
#define KAMERA_H

#include "ressourcen.h"

class Kamera
{
public:
    explicit Kamera(const char* pfad);
    void nehmeAuf(const char* pfad);

private:
    cv::VideoCapture videostream;
    cv::Mat bild;
    const char* pwd;
};

#endif // KAMERA_H
