#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#define PFAD "C:/SP3/gefundeneObjekteTest.txt"
#define DCLASS "detection_classes"
#define DSCORE "detection_scores"
#define DBOX "detection_boxes"
#define MAXLESEN 100

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

class Textauswerter : public QWidget
{
    Q_OBJECT

public:
    Textauswerter(QWidget *parent = nullptr);
    int werteAus();
    bool detection_classes(int aktlZeile);
    bool detection_scores(int aktlZeile);
    bool detection_boxes(int aktlZeile);
    ~Textauswerter();

private:
    int anzGlsnZeilen;
};

#endif // TEXTAUSWERTER_H
