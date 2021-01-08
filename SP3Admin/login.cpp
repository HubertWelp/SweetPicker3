#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    Monitor m;
    KonfigAdmin k;
}

Login::~Login()
{
    delete ui;
}

void Login::anmeldeAnfrage()
{
    if (ui->lineeditPasswort->text() == k.getPasswort())
    {
        m.show();
        //QMessageBox::information(this,"Anmelden","Richtige Daten");
    }

    else
    {
        QMessageBox::information(this,"Anmelden","Falsche Daten");
    }

    ui->lineeditPasswort->setText("");
}


void Login::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Return) anmeldeAnfrage();
    if (pe->key() == Qt::Key_Escape) close() ;
}
