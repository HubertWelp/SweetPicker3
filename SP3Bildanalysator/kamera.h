#ifndef KAMERA_H
#define KAMERA_H

#include "ressourcen.h"

class Kamera
{
public:
    explicit Kamera(const char* pfad);
    int nehmeAuf(const char* pfad);
    void nehmeAufTest(const char* pfad);
    int setzeKameraID(int idnew = 0);

private:
    cv::VideoCapture videostream;
    cv::Mat bild;
    const char* pwd;
    int id;
};

#endif // KAMERA_H
