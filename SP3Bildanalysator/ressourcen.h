#ifndef RESSOURCEN_H
#define RESSOURCEN_H

/* Definition von Konstanten */
#define PWD "/home/Student/git/SweetPicker3/SP3Bildanalysator"
#define BILDABLAGE "/SP3Bilderkennung/aktuelleSzene.jpg"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"
#define PROGNAME "/home/Student/git/SweetPicker3/SP3Objekterkenner/SP3Objekterkenner.py"

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

#endif // RESSOURCEN_H
