#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#define PFAD "C:/SP3/gefundeneObjekteTest.txt"
#define DCLASS "detection_classes"
#define DSCORE "detection_scores"
#define DBOX "detection_boxes"
#define MAXLESEN 40

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

class Textauswerter : public QWidget
{
    Q_OBJECT

public:
    Textauswerter(QWidget *parent = 0);
    bool werteAus();
    bool detection_classes(const QString zeile);
    bool detection_scores(const QString zeile);
    bool detection_boxes(const QString zeile);
    ~Textauswerter();

private:
    int anzGlsnZeilen;
};

#endif // TEXTAUSWERTER_H
