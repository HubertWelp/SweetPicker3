#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);

    KonfigAdmin k;
    Objektinformation info;
    info.setBildablage(k.getAblageort());

    // Aktuelle Parameter auf der Konfigurationsdatei einlesen und zwischenspeichern
    previousBildbreite = k.getBildbreite();
    previousBildhoehe = k.getBildhoehe();
    previousKameraID = k.getKameraID();
    previousRahmendicke = k.getRahmendicke();
    previousRahmenfarbe = k.getRahmenfarbe();

    // Werte der Parameter als Ausgangswerte der Eingabe setzen
    ui->spinBox_erode->setValue(previousBildbreite);
    ui->spinBox_dillate->setValue(previousBildhoehe);
    ui->spinBox_kameraID->setValue(previousKameraID);
    ui->spinBox_rahmendicke->setValue(previousRahmendicke);

    // Die Farbe des Druckknopfes zur Farbpalette einfärben
    QString qss = QString("background-color: %1").arg(previousRahmenfarbe.name());
    ui->pushButton_farbpalette->setStyleSheet(qss);

    zeichneInfo();

}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::parameterSpeichern()
{
    if(
        k.setBildbreite(ui->spinBox_erode->value()) ||
        k.setBildhoehe(ui->spinBox_dillate->value()) ||
        k.setKameraID(ui->spinBox_kameraID->value()) ||
        k.setRahmenfarbe(nextRahmenfarbe)  ||
        k.setRahmendicke(ui->spinBox_rahmendicke->value()) == 0
        )
    {
        // Aktuell eingestellte Werte der Eingabe als nächste Ausgangswerte setzen
        previousBildbreite = ui->spinBox_erode->value();
        previousBildhoehe = ui->spinBox_dillate->value();
        previousKameraID = ui->spinBox_kameraID->value();
        previousRahmendicke = ui->spinBox_rahmendicke->value();
        previousRahmenfarbe = nextRahmenfarbe;
        QMessageBox::information(this,"Parameter speichern","Parameter erfolgreich gespeichert");
    }
    else QMessageBox::information(this,"Parameter speichern","Speichern fehlgeschlagen");

}

void Monitor::erodeZuruecksetzen()
{
    ui->spinBox_erode->setValue(previousBildbreite);
}

void Monitor::dillateZuruecksetzen()
{
    ui->spinBox_dillate->setValue(previousBildhoehe);
}

void Monitor::kameraIDZuruecksetzen()
{
    ui->spinBox_kameraID->setValue(previousKameraID);
}

void Monitor::rahmendickeZuruecksetzen()
{
    ui->spinBox_rahmendicke->setValue(previousRahmendicke);
}

void Monitor::rahmenfarbeZuruecksetzen()
{
    QString qss = QString("background-color: %1").arg(previousRahmenfarbe.name());
    ui->pushButton_farbpalette->setStyleSheet(qss);
}

void Monitor::zeigeFarbpalette()
{
    nextRahmenfarbe = QColorDialog::getColor(previousRahmenfarbe, this);
    if(nextRahmenfarbe.isValid()){
        QString qss = QString("background-color: %1").arg(nextRahmenfarbe.name());
        ui->pushButton_farbpalette->setStyleSheet(qss);
    }
}

void Monitor::aktualisieren()
{
    if(info.aktualisieren() != 0)
    {
        zeichneInfo();
        QMessageBox::information(this,"Informationen laden","Dateien nicht lesbar.");
    }
    else
    {
        zeichneInfo();
    }

}

void Monitor::keyPressEvent(QKeyEvent *pe)
{
    if (pe->key() == Qt::Key_F5) aktualisieren();
    if (pe->key() == Qt::Key_Escape) close() ;
}

void Monitor::resizeEvent(QResizeEvent *re)
{
    zeichneInfo();
}

void Monitor::zeichneInfo()
{
    int w = ui->tab->size().width();
    int h = ui->tab->size().height();
    ui->label_aktuelleSzeneRahmen->setPixmap(QPixmap::fromImage(info.getAktuelleSzeneRahmen()).scaled(w, h, Qt::KeepAspectRatio));

    w = ui->label_ausschnitt->size().width();
    h = ui->label_ausschnitt->size().height();
    ui->label_ausschnitt->setPixmap(QPixmap::fromImage(info.getAusschnitt()).scaled(w, h, Qt::KeepAspectRatio));
    ui->label_ausschnittSW->setPixmap(QPixmap::fromImage(info.getAusschnittSW()).scaled(w, h, Qt::KeepAspectRatio));
    ui->label_ausschnittSWprocessed->setPixmap(QPixmap::fromImage(info.getAusschnittSWprocessed()).scaled(w, h, Qt::KeepAspectRatio));
    ui->label_ausschnittErgebnis->setPixmap(QPixmap::fromImage(info.getAusschnittErgebnis()).scaled(w, h, Qt::KeepAspectRatio));

    ui->lineEdit_xPosition->setText(QString::number(info.getXPosi())+" mm");
    ui->lineEdit_yPosition->setText(QString::number(info.getYPosi())+ " mm");
    ui->lineEdit_suessigkeit->setText(info.getAngefordertesObjekt());
    ui->lineEdit_breite->setText(QString::number(info.getBreite())+" mm");
    ui->lineEdit_orientierung->setText(QString::number(info.getWinkel())+"°");
}
