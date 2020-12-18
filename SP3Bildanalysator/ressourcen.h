#ifndef RESSOURCEN_H
#define RESSOURCEN_H

/* Definition von Konstanten */
#define PWD "/home/Student/git/SP3/SweetPicker3/SP3Bildanalysator"
#define BILD "aktuelleSzene.jpg"
#define ERKNT "gefundeneObjekte.jpg"
#define BILDABLAGE "/SP3Bilderkennung/"
#define AUSSCHNITT "Ausschnitt.jpg"
#define AUSSCHNITTSW "AusschnittSW.jpg"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"
#define PROGNAME "/home/Student/git/SP3/SweetPicker3/SP3Objekterkenner/SP3Objekterkenner.py"
#define PFAD "/home/Student/Downloads/gefundeneObjekte.txt"
#define DCLASS "detection_classes"
#define DSCORE "detection_scores"
#define DBOX "detection_boxes"
#define MAXLESEN 100    // Anzahl der aus der Textdatei ins Array einzulesenden Elemente
#define ANZELEMENT 105  // Größe des Arrays (5 Elemente Puffer)
#define ANZSUCHE 10     // Maximale Anzahl der auszusuchenden Elemente (die Indexe der 10 zuerst auftauchenden Klassen werden ermittelt)
#define BILDBRT 354     // Echte Bildbreite in mm
#define BILDHHE 274     // Echte Bildhöhe in mm
#define MAOMBREITE 50

/* Einbindung von Qt Bibliotheken */
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileInfo>
#include <QColor>

/* Einbindung von c Bibliotheken */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* */
#include <dirent.h>

/*SP3Admin*/
#include "../SP3Admin/konfig.h"

/* Einbindung von c++ Bibliotheken */
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <fstream>

/* Einbindung der opencv Bibliotheken */
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

/* Selbstdefinierte Strukturen und Enums */
struct RBox {double a; double b; double c; double d;};
struct Punkt {int x;int y;int z;};
struct Punkte {double ymin; double xmin; double ymax; double xmax;};
enum Sorten {Maoam=1,Snickers,Milkyway,Schokoriegel};

#endif // RESSOURCEN_H
