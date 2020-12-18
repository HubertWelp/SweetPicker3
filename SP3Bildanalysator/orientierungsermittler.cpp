#include "orientierungsermittler.h"
//achtung spaghetti

OrientierungsErmittler::OrientierungsErmittler(unsigned short morphOpenSize)
{

    this->morphOpenSize = cv::Size(morphOpenSize,morphOpenSize);
    /*Standardwerte*/
    this->bildPfad.append(PWD).append(BILDABLAGE).append(BILD);
    this->rahmenFarbe = qColor2CVScalar(QColor(3,128,148));
    this->rahmenDicke = 16;
}

int OrientierungsErmittler::setzeKoordinaten(double yMin, double xMin, double yMax, double xMax)
{
    this->yMin = yMin;
    this->xMin = xMin;
    this->yMax = yMax;
    this->xMax = xMax;

    return 0;
}

int OrientierungsErmittler::setzeBildPfad(const std::string &pfad)
{

    /*Prüfen ob der Pfad zurückgesetzt werden soll*/
    if(pfad.empty())
    {
        this->bildPfad.append(PWD).append(BILDABLAGE).append(BILD); //Standardpfad
        return 0;
    }

    /*Prüfen ob der angegebene Pfad gültig ist, also ein Bild enthält*/
    if(!cv::haveImageReader(pfad))
    {
        return 1; //Bild kann von opencv nicht dekodiert werden (korrupt oder nicht vorhanden)
    }else
    {
        bildPfad = pfad;
        return 0;
    }
}

int OrientierungsErmittler::ladeBild()
{
    bildInput = imread(bildPfad, cv::IMREAD_COLOR);
    if(bildInput.empty())
    {
        std::cout << "error bildInput" << std::endl;
        return -1;
    }
    return 0;
}

std::tuple<int, double, double> OrientierungsErmittler::ermittleOrientierung()
{

    double breite = 0; //TODO aus konfig nehmen

    //ladeParameter

    if(this->ladeBild() != 0)
    {
        return std::make_tuple(-1,0,0);
    }
    if(this->ausschnittROI() != 0)
    {
        return std::make_tuple(-2,0,0);
    }
    if(this->bearbeiteBild() != 0)
    {
        return std::make_tuple(-3,0,0);
    }

    std::vector<std::vector<cv::Point>> contours;
    cv::Mat contourOutput = bildAusschnittSchwarzWeissBearbeitet.clone();
    cv::findContours(contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

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

    /*Winkelberechnung*/
    double angle = atan2(eigenVecs[0].y, eigenVecs[0].x) * (180/CV_PI);

    //Winkel entspricht der Richtung vom blauen Pfeil, Orientierung ist manchmal gedreht.
    cv::Point p1 = center + 0.02 * cv::Point(static_cast<int>(eigenVecs[0].x * eigenVals[0]), static_cast<int>(eigenVecs[0].y * eigenVals[0]));
    cv::Point p2 = center - 0.02 * cv::Point(static_cast<int>(eigenVecs[1].x * eigenVals[1]), static_cast<int>(eigenVecs[1].y * eigenVals[1]));
    drawAxis(bildAusschnittBreit, center, p1, cv::Scalar(0, 255, 0), 1);
    drawAxis(bildAusschnittBreit, center, p2, cv::Scalar(255, 255, 0), 2);


    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("ausschnittErgebnis.jpg"),bildAusschnittBreit(ROI)); //der weiße Hintergrund wird rausgeschnitten da dieser nur notwendig war um die Kontur richtig einzuzeichnen

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("ausschnittErgebnis.jpg")))
    {
        return std::make_tuple(-4,angle,breite); //gespeichertes Bild kann von opencv nicht dekodiert werden (korrupt)
    }


    std::string pfadErgebnis = std::string(PWD).append(BILDABLAGE).append("gefundeneObjekte.jpg");

    /*Prüfen ob der Pfad ein Bild enthält*/
    if(!cv::haveImageReader(pfadErgebnis))
    {
        return std::make_tuple(-5,angle,breite);
    }

    bildAktuelleSzeneRahmen = cv::imread(pfadErgebnis);

    cv::rectangle(bildAktuelleSzeneRahmen, bildInputROI, rahmenFarbe, rahmenDicke, cv::LINE_AA); //TODO PARAM: Farbe, Dicke

    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("aktuelleSzeneRahmen.jpg"),bildAktuelleSzeneRahmen); //der weiße Hintergrund wird rausgeschnitten da dieser nur notwendig war um die Kontur richtig einzuzeichnen
    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("aktuelleSzeneRahmen.jpg")))
    {
        return std::make_tuple(-6,angle,breite); //gespeichertes Bild kann von opencv nicht dekodiert werden (korrupt)
    }

    //std::cout << "grad: " << angle<< std::endl;
    return std::make_tuple(0,angle,breite);
}

int OrientierungsErmittler::setzeRahmen(QColor farbe, unsigned int dicke)
{
    this->rahmenFarbe = qColor2CVScalar(farbe);
    this->rahmenDicke = dicke;
    return 0;
}

int OrientierungsErmittler::setzeRahmen(cv::Scalar farbe, unsigned int dicke)
{
    this->rahmenFarbe = farbe;
    this->rahmenDicke = dicke;
    return 0;
}

int OrientierungsErmittler::setzeRahmenFarbe(QColor farbe)
{
    this->rahmenFarbe = qColor2CVScalar(farbe);
    return 0;
}

int OrientierungsErmittler::setzeRahmenFarbe(cv::Scalar farbe)
{
    this->rahmenFarbe = farbe;
    return 0;
}

int OrientierungsErmittler::setzeRahmenDicke(unsigned int dicke)
{
    this->rahmenDicke = dicke;
    return 0;
}

QColor OrientierungsErmittler::getRahmenFarbeQColor()
{
    return cvScalar2QColor(rahmenFarbe);
}

cv::Scalar OrientierungsErmittler::getRahmenFarbeCVScalar()
{
    return rahmenFarbe;
}

unsigned int OrientierungsErmittler::getRahmenDicke()
{
    return rahmenDicke;
}

int OrientierungsErmittler::ausschnittROI()
{
    if(xMin < 1 && xMax < 1 && yMin < 1 && yMax < 1)
    {
        //Umrechnung und Rundung von normalisierten Koordinaten auf absoulte Koordinaten bezogen auf bildInput
        bildInputROI.x = static_cast<int>((bildInput.size().width * xMin) + 0.5);
        bildInputROI.y = static_cast<int>((bildInput.size().height * yMin) + 0.5);
        bildInputROI.width = static_cast<int>((bildInput.size().width * (xMax-xMin) + 0.5));
        bildInputROI.height = static_cast<int>((bildInput.size().height * (yMax-yMin) + 0.5));
    }
    else
    {
        //Falls Koordinaten nicht normalisiert angegeben werden und somit nicht umgerechnet werden müssen
        bildInputROI.x = static_cast<int>(xMin);
        bildInputROI.y = static_cast<int>(yMin);
        bildInputROI.width = static_cast<int>(xMax-xMin);
        bildInputROI.height = static_cast<int>(yMax-yMin);
    }

    if(bildInputROI.x == bildInputROI.width || bildInputROI.y == bildInputROI.height) return -1; //Ungültiger Rahmen (Koordinaten liegen auf einer 0px breiten/hohen Linie oder auf einem Punkt


    //std::cout << "ROI.x = " << ROI.x << " ROI.y = " << ROI.y << " ROI.width = " << ROI.width << " ROI.height = " << ROI.height << " BildBreite = " << bildInput.size().width << " Bildhöhe = " << bildInput.size().height << std::endl;

    bildAusschnitt = bildInput(bildInputROI);
    if(bildAusschnitt.empty())
    {
        return -2;
    }

    //cv::imwrite(std::string(PWD).append(BILDABLAGE).append("ausschnitt2.jpg"),cv::imread("/home/Student/git/SP3/SweetPicker3/SP3Bildanalysator/SP3Bilderkennung/gefundeneObjekte.jpg",cv::IMREAD_COLOR)(ROI));

    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("ausschnitt.jpg"),bildAusschnitt);
    cvtColor(bildAusschnitt,bildAusschnitGraustufe,cv::COLOR_BGR2GRAY);

    threshold(bildAusschnitGraustufe,bildAusschnittSchwarzWeiss,164,255,cv::THRESH_BINARY);//TODO PARAM

    cv::Mat bildAusschnittBreit = cv::Mat::zeros(bildAusschnitt.size().height + 100 , bildAusschnitt.size().width + 100, CV_8UC1);
    bildAusschnittBreit.setTo(cv::Scalar(255,255,255));
    bildAusschnittSchwarzWeiss.copyTo(bildAusschnittBreit(cv::Rect(50,50,bildAusschnittSchwarzWeiss.cols, bildAusschnittSchwarzWeiss.rows)));

    bildAusschnittBreit.copyTo(bildAusschnittSchwarzWeiss);
    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("ausschnittSW.jpg"),bildAusschnittSchwarzWeiss(cv::Rect(50,50,bildAusschnitt.cols, bildAusschnitt.rows)));

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("ausschnitt.jpg")) || !cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("ausschnittSW.jpg")))
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
    cv::morphologyEx(bildAusschnittSchwarzWeiss,bildAusschnittSchwarzWeissBearbeitet,cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE,morphOpenSize)); //remove noise
    cv::imwrite(std::string(PWD).append(BILDABLAGE).append("ausschnittSWprocessed.jpg"),bildAusschnittSchwarzWeissBearbeitet(cv::Rect(50,50,bildAusschnitt.cols, bildAusschnitt.rows)));

    if(!cv::haveImageReader(std::string(PWD).append(BILDABLAGE).append("ausschnittSWprocessed.jpg")))
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
    //! [visualization]
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
    //! [visualization]
}

cv::Scalar OrientierungsErmittler::qColor2CVScalar(QColor color)
{
    int r,g,b;
    color.getRgb(&r, &g, &b);
    //std::cout << r << " " << g << " " << b << std::endl;
    return cv::Scalar(b,g,r); // swap RGB-->BGR
}

QColor OrientierungsErmittler::cvScalar2QColor(cv::Scalar color)
{
    return QColor(color[2],color[1],color[0]); // swap RGB-->BGR
}
