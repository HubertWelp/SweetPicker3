#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include "konfig.h"
#include "objektinformation.h"

namespace Ui {
class Monitor;
}

class Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Monitor(QWidget *parent = nullptr);
    ~Monitor() override;

public slots:
    void parameterSpeichern();
    void erodeZuruecksetzen();
    void dillateZuruecksetzen();
    void kameraIDZuruecksetzen();
    void rahmendickeZuruecksetzen();
    void rahmenfarbeZuruecksetzen();
    void zeigeFarbpalette();
    void aktualisieren();
    void keyPressEvent(QKeyEvent* pe) override;
    void resizeEvent(QResizeEvent*) override;

private:
    Ui::Monitor *ui;

    KonfigAdmin k;
    Objektinformation info;
    int previousBildbreite;
    int previousBildhoehe;
    int previousKameraID;
    int previousRahmendicke;
    QColor previousRahmenfarbe;
    QColor nextRahmenfarbe;
    void zeichneInfo();
};

#endif // MONITOR_H
