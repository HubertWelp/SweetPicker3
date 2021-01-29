#include "konfig.h"

#include <iostream>
#include <QTextStream>

Konfig::Konfig(QString pfad)
{
    dateipfad=pfad;
}

QString Konfig::getAblageort()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    QString c;
    settings.beginGroup("Allgemein");
    if(settings.contains("Ablage") && settings.status()==0)
    {
        c = settings.value("Ablage").toString();
    }
    else c = "/home/Student/git/SP3/SweetPicker3/SP3Bildanalysator/SP3Bilderkennung";
    settings.endGroup();

    return c;
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

float Konfig::getObjektbreite(int nr)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    float c;
    settings.beginGroup("Objektbreiten");
    if(settings.contains("Objekt"+QString::number(nr)) && settings.status()==0)
    {
        c = settings.value("Objekt"+QString::number(nr)).toFloat();
    }
    else c = -1;
    settings.endGroup();

    return c;
}

int Konfig::getBildbreite()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Kamera");
    if(settings.contains("Bildbreite") && settings.status()==0)
    {
        c = settings.value("Bildbreite").toInt();
    }
    else c = -1;
    settings.endGroup();

    return c;
}

int Konfig::getBildhoehe()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Kamera");
    if(settings.contains("Bildhoehe") && settings.status()==0)
    {
        c = settings.value("Bildhoehe").toInt();
    }
    else c = -1;
    settings.endGroup();

    return c;
}

int Konfig::getRahmendicke()
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    int c;
    settings.beginGroup("Parameter");
    if(settings.contains("Rahmendicke") && settings.status()==0)
    {
        c = settings.value("Rahmendicke").toInt();
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
    if(settings.contains("Rahmenfarbe"))
    {
        c = settings.value("Rahmenfarbe").value<QColor>();
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
    settings.beginGroup("Allgemein");
    if(settings.contains("pw") && settings.status()==0)
    {
        c = settings.value("pw").toString();
    }
    else c = "SP3";
    settings.endGroup();

    return c;
}

int KonfigAdmin::setRahmendicke(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Parameter");
    settings.setValue("Rahmendicke",input);
    settings.endGroup();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setRahmenfarbe(QColor farbe)
{
    QTextStream out(stdout);
    out << dateipfad << endl;

    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Parameter");
    settings.setValue("Rahmenfarbe",farbe.name());
    settings.endGroup();
    settings.sync();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setBildbreite(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Kamera");
    settings.setValue("Bildbreite",input);
    settings.endGroup();
    if(settings.status()==0) return 0;
    else return -1;
}

int KonfigAdmin::setBildhoehe(int input)
{
    QSettings settings(dateipfad,QSettings::IniFormat);
    settings.beginGroup("Kamera");
    settings.setValue("Bildhoehe",input);
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
