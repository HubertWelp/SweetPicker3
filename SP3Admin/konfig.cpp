#include "konfig.h"

#include <iostream>
#include <QTextStream>

Konfig::Konfig(QString pfad)
{
    dateipfad=pfad;
}

QString Konfig::getObjektname(int nr)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    QString c;
    settings.beginGroup("Objektnamen");
    if(settings.contains("Objekt"+QString::number(nr)) && settings.status()==0)
    {
        c = settings.value("Objekt"+QString::number(nr)).toString();
    }
    else c = "";
    settings.endGroup();

    return c;
}

int Konfig::getErode()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Parameter");
    if(settings.contains("erode") && settings.status()==0)
    {
        c = settings.value("erode").toInt();
    }
    else c = -1;
    settings.endGroup();

    return c;
}

int Konfig::getDillate()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Parameter");
    if(settings.contains("dillate") && settings.status()==0)
    {
        c = settings.value("dillate").toInt();
    }
    else c = -1;
    settings.endGroup();

    return c;
}

QColor Konfig::getRahmenfarbe()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    QColor c;
    settings.beginGroup("Parameter");
    if(settings.contains("rahmenfarbe"))
    {
        c = settings.value("rahmenfarbe").value<QColor>();
    }
    else c = QColor::fromRgb(255,255,255);
    settings.endGroup();

    return c;
}

int Konfig::getKameraID()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Kamera");
    if(settings.contains("id") && settings.status()==0)
    {
        c = settings.value("id").toInt();
    }
    else c = -1;
    settings.endGroup();

    return c;
}


KonfigAdmin::KonfigAdmin(QString pfad)
{
    dateipfad=pfad;
}

QString KonfigAdmin::getPasswort()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    QString c;
    settings.beginGroup("Passwort");
    if(settings.contains("pw") && settings.status()==0)
    {
        c = settings.value("pw").toString();
    }
    else c = "SP3";
    settings.endGroup();

    return c;
}

int KonfigAdmin::setRahmenfarbe(QColor farbe)
{
    QTextStream out(stdout);
    out << dateipfad << endl;

    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Parameter");
    settings.setValue("rahmenfarbe",farbe.name());
    settings.endGroup();
    settings.sync();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setErode(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Parameter");
    settings.setValue("erode",input);
    settings.endGroup();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setDillate(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Parameter");
    settings.setValue("dillate",input);
    settings.endGroup();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setKameraID(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Kamera");
    settings.setValue("id",input);
    settings.endGroup();
    if(settings.status()==0) return 0;
    else return -1;
}
