#ifndef RESSOURCEN_H
#define RESSOURCEN_H

/* Definition von Konstanten */
#define PWD "/home/Student/git/SP3/SweetPicker3/SP3Bildanalysator"
#define BILDABLAGE "/SP3Bilderkennung/aktuelleSzene.png"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"
#define PROGNAME "/home/Student/git/SP3/SweetPicker3/SP3Objekterkenner/SP3Objekterkenner.py"
#define PFAD "/home/Student/Downloads/gefundeneObjekte.txt"
#define DCLASS "detection_classes"
#define DSCORE "detection_scores"
#define DBOX "detection_boxes"
#define MAXLESEN 100    // Anzahl der aus der Textdatei ins Array einzulesenden Elemente
#define ANZELEMENT 105  // Größe des Arrays (5 Elemente Puffer)
#define ANZSUCHE 10     // Maximale Anzahl der auszusuchenden Elemente (die Indexe der 10 zuerst auftauchenden Klassen werden ermittelt)
#define BILDBRT 290     // Echte Bildbreite in mm
#define BILDHHE 195     // Echte Bildhöhe in mm

/* Einbindung von Qt Bibliotheken */
#include <QFile>
#include <QTextStream>
#include <QString>

/* Einbindung von c Bibliotheken */
#include <stdio.h>
#include <string.h>

/* Einbindung von c++ Bibliotheken */
#include <chrono>
#include <thread>

/* Einbindung der opencv Bibliotheken */
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>

/* Selbstdefinierte Strukturen und Enums */
struct RBox {double a; double b; double c; double d;};
struct Punkt {int x;int y;int z;};
enum Sorten {Maoam=1,Snickers,Milkyway,Schokoriegel};

#endif // RESSOURCEN_H
