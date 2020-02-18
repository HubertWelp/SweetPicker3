#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPicture>
#include <QPixmap>
#include <QFont>
#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include "clicklabel.h"
#include "sortenorter.h"
#include "udpnode.hpp"

class Monitor : public QWidget
{
    Q_OBJECT
public:
    explicit Monitor(QWidget *parent = nullptr);

signals:

public slots:
    void aktualisiert();

private:
    QLabel* logo ;              // eigentlich ein Bild
    QLabel* ueberschrift ;      // Name des Bildschirms
    ClickLabel* beenden ;           // eigentlich ein Button
    QLabel* parameter ;         // Label Parameter
    QLabel* kamera ;            // Label Kamera
    QLabel* bildverarbeitung ;  // Label Bildverarbeitung
    QLabel* bilderkennung ;     // Label Bilderkennung
    QLabel* anzErkObj ;         // Label für die Anzahl der erkannten Objekte
    QLabel* bild;               // die aktuelleSzene.jpg
    QLineEdit* kW1;             // Wert 1 für Kamera
    QLineEdit* kW2;             // Wert 2 für Kamera
    QLineEdit* bvW1;            // Wert 1 für Bildverarbeitung
    QLineEdit* bvW2;            // Wert 2 für Bildverarbeitung
    QPushButton* andUber;       // Button zur Übernahme der Änderungen
    SortenOrter* orter;

    int anzObj;
};

#endif // MONITOR_H
