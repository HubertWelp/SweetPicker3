#include "login.h"
#include "ui_login.h"

LOGIN::LOGIN(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LOGIN)
{
    ui->setupUi(this);
    MONITOR m;
    KonfigAdmin k;
}

LOGIN::~LOGIN()
{
    delete ui;
}

void LOGIN::anmeldeAnfrage()
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


void LOGIN::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_Return) anmeldeAnfrage();
    if (pe->key() == Qt::Key_Escape) close() ;
}
