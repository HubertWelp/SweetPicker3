#include "monitor.h"

Monitor::Monitor(QWidget *parent) : QWidget(parent)
{
    logo = new QLabel;
    QPixmap bildLogo(":/thga_logo.jpg"); bildLogo = bildLogo.scaledToHeight(80);
    logo->setPixmap(bildLogo);
    ueberschrift = new QLabel("Admin: Einstellungen und Debugging");
    beenden = new ClickLabel;
    QPixmap exitBild (":/exit.png");
    exitBild = exitBild.scaledToWidth(30);
    beenden->setPixmap(exitBild);
    parameter = new QLabel("Parameter:");
    kamera = new QLabel("Kamera:");
    bildverarbeitung = new QLabel("Bildverarbeitung:");
    bilderkennung = new QLabel("Bilderkennung:");
    anzErkObj = new QLabel("Anzahl erkannter Objekte: ");
    anzObj = 0;
    bild = new QLabel;
    kW1 = new QLineEdit("Wert 1");
    kW1->setReadOnly(true);
    kW2 = new QLineEdit("Wert 2");
    kW2->setReadOnly(true);
    bvW1 = new QLineEdit("Wert 1");
    bvW1->setReadOnly(true);
    bvW2 = new QLineEdit("Wert 2");
    bvW2->setReadOnly(true);
    andUber = new QPushButton("Änderungen\nübernehmen!");

    QHBoxLayout* titel = new QHBoxLayout;
    titel->addWidget(beenden);
    titel->addWidget(ueberschrift);
    titel->addWidget(logo);

    QVBoxLayout* paraLayout  = new QVBoxLayout;
    paraLayout->addWidget(parameter);
    paraLayout->addWidget(kamera);
    paraLayout->addWidget(kW1);
    paraLayout->addWidget(kW2);
    paraLayout->addWidget(bildverarbeitung);
    paraLayout->addWidget(bvW1);
    paraLayout->addWidget(bvW2);
    paraLayout->addWidget(andUber);

    QVBoxLayout* ausgLayout  = new QVBoxLayout;
    ausgLayout->addWidget(bilderkennung);
    ausgLayout->addWidget(bild);
    ausgLayout->addWidget(anzErkObj);

    QHBoxLayout* inhalt  = new QHBoxLayout;
    inhalt->addLayout(paraLayout);
    inhalt->addLayout(ausgLayout);

    QVBoxLayout* main = new QVBoxLayout;
    main->addLayout(titel);
    main->addLayout(inhalt);

    setLayout(main);
    connect(beenden,SIGNAL(clicked()),this,SLOT(close()));
}
