#include "gui.h"

GUI::GUI()
{
    orter = new SortenOrter("/home/Student/Bilder/Webcam/","aktuelleSzene.jpg");
    orter->gebeKoordinatenein(100,100,300,300); // müssen noch entsprechend eingegeben

    ueberschrift = new QLabel("Login zum Debugging:",this);
    ueberschrift->setAlignment(Qt::AlignCenter);
    passLabel = new QLabel("Admin Login: ",this);

    passEingabe = new QLineEdit(this);
    passEingabe->setEchoMode(QLineEdit::Password);

    anmelden = new QPushButton("anmelden",this);

    beenden = new ClickLabel;
    QPixmap exitBild (":/exit.png");
    exitBild = exitBild.scaledToWidth(30);
    beenden->setPixmap(exitBild);

    zuruck = new QPushButton("zurück",this);
    zuruck->setFixedWidth(80);

    QFont schrift;
    schrift.setBold(true);
    schrift.setPixelSize(14);
    ueberschrift->setFont(schrift);

    logo = new ClickLabel;
    bildLogo.load(":/thga_logo.jpg"); bildLogo = bildLogo.scaledToHeight(80);
    logo->setPixmap(bildLogo);

    oben = new QHBoxLayout;
    oben->addWidget(beenden);
    oben->addWidget(ueberschrift);
    oben->addWidget(logo);

    mitte = new QVBoxLayout;
    mitte->addWidget(passLabel);
    mitte->addWidget(passEingabe);
    mitte->addWidget(anmelden);

    unten = new QHBoxLayout;
    unten->addWidget(zuruck);
    unten->setAlignment(Qt::AlignLeft);

    main = new QVBoxLayout;
    main->addLayout(oben);
    main->addLayout(mitte);
    main->addLayout(unten);

    easegg = 0;

    connect(anmelden,SIGNAL(clicked()),this,SLOT(anmeldeAnfrage()));
    connect(beenden,SIGNAL(clicked()),this,SLOT(close()));
    connect(zuruck,SIGNAL(clicked()),this,SLOT(close()));
    connect(logo,SIGNAL(clicked()),this,SLOT(easteregg()));

    setLayout(main);
    setWindowTitle(tr("Sweet Picker 3 - Admin"));
}

void GUI::anmeldeAnfrage()
{
    if (passEingabe->text() == PASS)
    {
        passEingabe->setText("");
        moni = new Monitor;
        moni->show();
    }
    else QMessageBox::information(this,"Anmelden","Falsche Daten"); passEingabe->setText("");
}

void GUI::zeigeMonitor()
{
    QMessageBox::information(this,"Zeigen","Monitor öffnet sich");
}

void GUI::easteregg()
{
    easegg++;
    if(easegg==3)
    {
        QMessageBox::information(this,"Easter Egg","Hurra ! Sie haben das Easter Egg gefunden");
        easegg = 0;
    }
}

void GUI::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Return) anmeldeAnfrage();
    if (pe->key() == Qt::Key_Escape) close() ;
}
