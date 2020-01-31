#include "gui.h"

GUI::GUI()
{
    orter = new SortenOrter("/home/Student/Bilder/Webcam/","aktuelleSzene.jpg");
    orter->gebeKoordinatenein(100,100,300,300); // müssen noch entsprechend eingegeben
    moni = new Monitor(this);

    logo = new QLabel(this);
    ueberschrift = new QLabel("Admin",this);
    ueberschrift->setAlignment(Qt::AlignCenter);
    nutzerLabel = new QLabel("Nutzername: ",this);
    passLabel = new QLabel("Passwort: ",this);

    nutzerEingabe = new QLineEdit(this);
    passEingabe = new QLineEdit(this);
    passEingabe->setEchoMode(QLineEdit::Password);

    anmelden = new QPushButton("anmelden !",this);
    beenden = new QPushButton("beenden !",this);
    zeichnen = new QPushButton("zeichnen !",this);

    QFont schrift;
    schrift.setBold(true);
    schrift.setPointSize(32);
    ueberschrift->setFont(schrift);

    bildLogo.load("/home/Student/SP3/logo.jpg"); bildLogo = bildLogo.scaledToHeight(80);
    logo->setPixmap(bildLogo);

    schicht1 = new QHBoxLayout;
    schicht1->addWidget(ueberschrift);
    schicht1->addWidget(logo);

    nutzer = new QHBoxLayout;
    nutzer->addWidget(nutzerLabel);
    nutzer->addWidget(nutzerEingabe);

    pass = new QHBoxLayout;
    pass->addWidget(passLabel);
    pass->addWidget(passEingabe);

    main = new QVBoxLayout;
    main->addLayout(schicht1);
    main->addLayout(nutzer);
    main->addLayout(pass);
    main->addWidget(anmelden);
    main->addWidget(zeichnen);
    main->addWidget(beenden);

    connect(anmelden,SIGNAL(clicked()),this,SLOT(anmeldeAnfrage()));
    connect(zeichnen,SIGNAL(clicked()),orter,SLOT(zeichne()));
    connect(zeichnen,SIGNAL(clicked()),this,SLOT(zeigeMonitor()));
    connect(beenden,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(main);
    setFixedSize(400,300);
    setWindowTitle(tr("Sweet Picker 3 - Admin"));
}

void GUI::anmeldeAnfrage()
{
    if (nutzerEingabe->text() == NUTZER && passEingabe->text() == PASS)
    {
        QMessageBox::information(this,"Anmelden","Richtige Daten");
    }
    else QMessageBox::information(this,"Anmelden","Falsche Daten");
}

void GUI::zeigeMonitor()
{
    QMessageBox::information(this,"Zeigen","Monitor öffnet sich");
}

void GUI::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Return) anmeldeAnfrage();
    if (pe->key() == Qt::Key_Escape) close() ;
}
