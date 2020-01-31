#include "gui.h"

GUI::GUI()
{
    logo = new QLabel(this);
    ueberschrift = new QLabel("Admin",this);
    nutzerLabel = new QLabel("Nutzername: ",this);
    passLabel = new QLabel("Passwort: ",this);
    nutzerEingabe = new QLineEdit(this);
    passEingabe = new QLineEdit(this);
    passEingabe->setEchoMode(QLineEdit::Password);
    anmelde = new QPushButton("anmelden !",this);

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
    main->addWidget(anmelde);

    connect(anmelde,SIGNAL(clicked()),this,SLOT(anmeldeAnfrage()));

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

void GUI::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Return) anmeldeAnfrage();
    if (pe->key() == Qt::Key_Escape) close() ;
}
