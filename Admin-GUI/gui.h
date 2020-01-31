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
    void keyPressEvent(QKeyEvent* pe) override;

private:
    QLabel* logo;
    QLabel* ueberschrift ;
    QLabel* nutzerLabel ;
    QLabel* passLabel ;
    QLineEdit* nutzerEingabe ;
    QLineEdit* passEingabe ;
    QPushButton* anmelde ;
    QFont schrift;
    QPixmap bildLogo;
    QHBoxLayout* schicht1;
    QHBoxLayout* nutzer;
    QHBoxLayout* pass;
    QVBoxLayout* main;
};

#endif // GUI_H
