#include "orientierungsermittler.h"
//achtung spaghetti

OrientierungsErmittler::OrientierungsErmittler(unsigned short morphOpenSize)
{
    this->morphOpenSize = cv::Size(morphOpenSize,morphOpenSize);
}

int OrientierungsErmittler::setzeKoordinaten(double yMin, double xMin, double yMax, double xMax)
{
    this->yMin = yMin;
    this->xMin = xMin;
    this->yMax = yMax;
    this->xMax = xMax;

    return 0;
}

int OrientierungsErmittler::ladeBild(const std::string &pfad = "")
{

    if(pfad.empty())
    {
        bildPfad.clear();
        bildPfad.append(PWD).append(BILDABLAGE).append(BILD); //Standardpfad

    }else
    {
        bildPfad.clear();
        bildPfad.append(pfad); //Manueller Pfad
    }
    //std::cout << "bildpfad: " << bildPfad << std::endl;
    bildInput = imread(bildPfad , cv::IMREAD_COLOR);
    if(bildInput.empty())
    {
        std::cout << "error bildInput" << std::endl;
        return -1;
    }
    return 0;
}

std::tuple<int, double, double> OrientierungsErmittler::ermittleOrientierung()
{


    //ladeParameter

    if(this->ladeBild() != 0)
    {
        return std::make_tuple(-1,0,0);
    }
    if(this->ausschnittROI() != 0)
    {
        return std::make_tuple(-1,0,0);
    }
    if(this->bearbeiteBild() != 0)
    {
        return std::make_tuple(-1,0,0);
    }

    std::vector<std::vector<cv::Point>> contours;
    cv::Mat contourOutput = bildAusschnittSchwarzWeissBearbeitet.clone();
    cv::findContours(contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    cv::Mat contourImage(bildAusschnittSchwarzWeissBearbeitet.size(), CV_8UC3, cv::Scalar(255,255,255));

    //Findet die zweitgrößte Fläche und seinen Index im Kontur Feld. Die größte Fläche entspricht der Bildfläche, die zweitgrößte Fläche entspricht mit sehr hoher Wahrscheinlichkeit der gesuchten Fläche

    double largestArea = 0;
    double secondlargestArea = 0;
    size_t largestAreaIDX = 0;
    size_t secondlargestAreaIDX = 0;
    for(size_t i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        if(area > largestArea)
        {
            secondlargestArea = largestArea;
            largestArea = area;
            secondlargestAreaIDX = largestAreaIDX;
            largestAreaIDX = i;
        }
    }

    //std::cout << "largest area: " << cv::contourArea(contours[secondlargestAreaIDX]) << std::endl;
    cv::drawContours(contourImage, contours, secondlargestAreaIDX, cv::Scalar(0,0,255),4);

    //Da die Schwarzweiß Bilder einen vergrößerten Hintergrundbekommen haben muss dies beim Zeichnen der Kontur berücksichtigt werden.
    cv::Mat bildAusschnittBreit = cv::Mat::zeros(bildAusschnitt.size().height + 100 , bildAusschnitt.size().width + 100, CV_8UC3);
    bildAusschnittBreit.setTo(cv::Scalar(255,255,255));
    cv::Rect ROI = cv::Rect(50,50,bildAusschnitt.cols, bildAusschnitt.rows);
    bildAusschnitt.copyTo(bildAusschnittBreit(ROI));

    cv::drawContours(bildAusschnittBreit, contours, secondlargestAreaIDX, cv::Scalar(0,0,255),4);

    //Berechne Orientierung

    //PCA
    int size = static_cast<int>(contours[secondlargestAreaIDX].size());
    cv::Mat dataPts = cv::Mat(size, 2, CV_64F);
    for(int i = 0; i < dataPts.rows; i++)
    {
        dataPts.at<double>(i,0) = contours[secondlargestAreaIDX][i].x;
        dataPts.at<double>(i,1) = contours[secondlargestAreaIDX][i].y;
    }

    cv::PCA pcaAnalysis(dataPts,cv::Mat(),cv::PCA::DATA_AS_ROW);

    //Store the center of the object
    center = cv::Point(static_cast<int>(pcaAnalysis.mean.at<double>(0,0)), static_cast<int>(pcaAnalysis.mean.at<double>(0,1)));

    //Store eigenvalues and eigenvectors
    std::vector<cv::Point2d> eigenVecs(2);
    std::vector<double> eigenVals(2);
    for(size_t i = 0; i < 2; i++)
    {
        eigenVecs[i] = cv::Point2d(pcaAnalysis.eigenvectors.at<double>(i,0),pcaAnalysis.eigenvectors.at<double>(i,1));

        eigenVals[i] = pcaAnalysis.eigenvalues.at<double>(i);
    }

    double angle = atan2(eigenVecs[0].y, eigenVecs[0].x) * (180/CV_PI);
    if(angle > 90)
    {
        angle = 450 - angle;
    }
    else
    {
        angle = 90 - angle;
    }

    //blau entspricht winkel
    cv::Point p1 = center + 0.02 * cv::Point(static_cast<int>(eigenVecs[0].x * eigenVals[0]), static_cast<int>(eigenVecs[0].y * eigenVals[0]));
    cv::Point p2 = center - 0.02 * cv::Point(static_cast<int>(eigenVecs[1].x * eigenVals[1]), static_cast<int>(eigenVecs[1].y * eigenVals[1]));
    drawAxis(bildAusschnittBreit, center, p1, cv::Scalar(0, 255, 0), 1);
    drawAxis(bildAusschnittBreit, center, p2, cv::Scalar(255, 255, 0), 2);


    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("AusschnittErgebnis.jpg"),bildAusschnittBreit(ROI)); //der weiße Hintergrund wird rausgeschnitten da dieser nur notwendig war um die Kontur richtig einzuzeichnen

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("AusschnittErgebnis.jpg")))
    {
        return std::make_tuple(-1,0,0); //gespeicherte Bilder können von opencv nicht dekodiert werden (korrupt)
    }

    double breite = 0;

    //std::cout << "grad: " << angle<< std::endl;
    return std::make_tuple(0,angle,breite);
}

int OrientierungsErmittler::ausschnittROI()
{
    cv::Rect ROI;

    if(xMin < 1 && xMax < 1 && yMin < 1 && yMax < 1)
    {
        //Umrechnung und Rundung von normalisierten Koordinaten auf absoulte Koordinaten bezogen auf bildInput
        ROI.x = static_cast<int>((bildInput.size().width * xMin) + 0.5);
        ROI.y = static_cast<int>((bildInput.size().height * yMin) + 0.5);
        ROI.width = static_cast<int>((bildInput.size().width * (xMax-xMin) + 0.5));
        ROI.height = static_cast<int>((bildInput.size().height * (yMax-yMin) + 0.5));
    }
    else
    {
        //Falls Koordinaten nicht normalisiert angegeben werden und somit nicht umgerechnet werden müssen
        ROI.x = static_cast<int>(xMin);
        ROI.y = static_cast<int>(yMin);
        ROI.width = static_cast<int>(xMax-xMin);
        ROI.height = static_cast<int>(yMax-yMin);
    }

    if(ROI.x == ROI.width || ROI.y == ROI.height) return -1; //Ungültiger Rahmen (Koordinaten liegen auf einer 0px breiten/hohen Linie oder auf einem Punkt


    //std::cout << "ROI.x = " << ROI.x << " ROI.y = " << ROI.y << " ROI.width = " << ROI.width << " ROI.height = " << ROI.height << " BildBreite = " << bildInput.size().width << " Bildhöhe = " << bildInput.size().height << std::endl;

    bildAusschnitt = bildInput(ROI);
    if(bildAusschnitt.empty())
    {
        return -2;
    }

    //cv::imwrite(std::string(PWD).append(BILDABLAGE).append("Ausschnitt2.jpg"),cv::imread("/home/Student/git/SP3/SweetPicker3/SP3Bildanalysator/SP3Bilderkennung/gefundeneObjekte.jpg",cv::IMREAD_COLOR)(ROI));
    cv::Mat bildAusschnitGraustufe;

    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("Ausschnitt.jpg"),bildAusschnitt);
    cvtColor(bildAusschnitt,bildAusschnitGraustufe,cv::COLOR_BGR2GRAY);

    threshold(bildAusschnitGraustufe,bildAusschnittSchwarzWeiss,164,255,cv::THRESH_BINARY);

    cv::Mat bildAusschnittBreit = cv::Mat::zeros(bildAusschnitt.size().height + 100 , bildAusschnitt.size().width + 100, CV_8UC1);
    bildAusschnittBreit.setTo(cv::Scalar(255,255,255));
    bildAusschnittSchwarzWeiss.copyTo(bildAusschnittBreit(cv::Rect(50,50,bildAusschnittSchwarzWeiss.cols, bildAusschnittSchwarzWeiss.rows)));

    bildAusschnittBreit.copyTo(bildAusschnittSchwarzWeiss);
    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("AusschnittSW.jpg"),bildAusschnittSchwarzWeiss(cv::Rect(50,50,bildAusschnitt.cols, bildAusschnitt.rows)));

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("Ausschnitt.jpg")) || !cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("AusschnittSW.jpg")))
    {
        return -3; //gespeicherte Bilder können von opencv nicht dekodiert werden (korrupt)
    }
    else
    {
        return 0;
    }

}

int OrientierungsErmittler::bearbeiteBild()
{
    //cv::Mat bildAusschnittSchwarzWeissBearbeitet;
    //cv::erode(bildAusschnittSchwarzWeiss,bildAusschnittSchwarzWeissBearbeitet,cv::getStructuringElement(cv::MORPH_ELLIPSE,erodeSize));


    cv::morphologyEx(bildAusschnittSchwarzWeiss,bildAusschnittSchwarzWeissBearbeitet,cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE,morphOpenSize)); //remove noise
    //cv::dilate(bildAusschnittSchwarzWeissBearbeitet,bildAusschnittSchwarzWeissBearbeitet,cv::getStructuringElement(cv::MORPH_ELLIPSE,morphOpenSize));

    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("AusschnittSWprocessed.jpg"),bildAusschnittSchwarzWeissBearbeitet(cv::Rect(50,50,bildAusschnitt.cols, bildAusschnitt.rows)));

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("AusschnittSWprocessed.jpg")))
    {
        return -1; //gespeichertes Bild kann von opencv nicht dekodiert werden (korrupt)
    }
    else
    {
        return 0;
    }
}

void OrientierungsErmittler::drawAxis(cv::Mat &img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale)
{
        //! [visualization1]
        double angle = atan2(static_cast<double>(p.y - q.y), static_cast<int>(p.x - q.x)); // angle in radians
        double hypotenuse = sqrt(static_cast<double>(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));

        // Here we lengthen the arrow by a factor of scale
        q.x = static_cast<int>(p.x - scale * hypotenuse * cos(angle));
        q.y = static_cast<int>(p.y - scale * hypotenuse * sin(angle));
        line(img, p, q, colour, 3, cv::LINE_AA);

        // create the arrow hooks
        p.x = static_cast<int>(q.x + 9 * cos(angle + CV_PI / 4));
        p.y = static_cast<int>(q.y + 9 * sin(angle + CV_PI / 4));
        line(img, p, q, colour, 3, cv::LINE_AA);

        p.x = static_cast<int>(q.x + 9 * cos(angle - CV_PI / 4));
        p.y = static_cast<int>(q.y + 9 * sin(angle - CV_PI / 4));
        line(img, p, q, colour, 3, cv::LINE_AA);
        //! [visualization1]
}
