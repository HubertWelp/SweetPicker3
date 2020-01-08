/*
*   Quelle für Kamera: https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html
*   Quelle für Timer: https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
*/
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
