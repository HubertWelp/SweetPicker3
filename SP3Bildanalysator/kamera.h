#ifndef KAMERA_H
#define KAMERA_H

#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

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
