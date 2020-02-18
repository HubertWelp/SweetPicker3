#ifndef GUI_H
#define GUI_H

/************************** Bibliotheken **************************/

#include <QWidget>              // Superklasse
#include <QGroupBox>            // für die Gruppierung im Layout
#include <QHBoxLayout>          // für die Horizontale Anordnung im Layout
#include <QVBoxLayout>          // für die Vertikale Anordnung im Layout
#include <QLabel>               // Überschriften für die Felder im Layout
#include <QTextEdit>            // für die Ausgabe auf einem Textfeld
#include <QLineEdit>
#include <QPicture>
#include <QPixmap>
#include <QFont>
#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include "monitor.h"
#include "clicklabel.h"

#define NUTZER "SP3"
#define PASS "SP3"

/********************* Deklaration der Klasse *********************/

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI();

public slots:
    void anmeldeAnfrage();
    void zeigeMonitor();
    void easteregg();
    void keyPressEvent(QKeyEvent* pe) override;

private:
    ClickLabel* logo;
    QLabel* ueberschrift ;
    QLabel* passLabel ;
    QLineEdit* passEingabe ;
    QPushButton* anmelden ;
    QPushButton* zuruck ;
    ClickLabel* beenden ;
    QFont schrift;
    QPixmap bildLogo;
    QHBoxLayout* oben;
    QVBoxLayout* mitte;
    QHBoxLayout* unten;
    QVBoxLayout* main;
    Monitor* moni;

    int easegg;
};

#endif // GUI_H
