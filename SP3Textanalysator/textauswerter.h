#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#define PFAD "C:/SP3/gefundeneObjekteTest.txt"
#define DCLASS "detection_classes"
#define DSCORE "detection_scores"
#define DBOX "detection_boxes"
#define MAXLESEN 100    // Anzahl der aus der Textdatei ins Array einzulesenden Elemente
#define ANZELEMENT 105  // Größe des Arrays (5 Elemente Puffer)
#define ANZSUCHE 10     // Maximale Anzahl der auszusuchenden Elemente (die Indexe der 10 zuerst auftauchenden Klassen werden ermittelt)
#define BILDBRT 640     // Bildbreite
#define BILDHHE 480     // Bildhöhe

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

struct RBox {double a; double b; double c; double d;};
struct Punkt {int x;int y;};

class Textauswerter : public QWidget
{
    Q_OBJECT

public:
    Textauswerter(QWidget *parent = nullptr);
    int liesEin();
    Punkt werteAus(int wk);
    bool detection_classes(int aktlZeile);
    bool detection_scores(int aktlZeile);
    bool detection_boxes(int aktlZeile);
    ~Textauswerter();

private:
    int ergK[ANZELEMENT];
    double ergW[ANZELEMENT];
    RBox ergB[ANZELEMENT];
    int anzGlsnZeilen;
};

#endif // TEXTAUSWERTER_H
