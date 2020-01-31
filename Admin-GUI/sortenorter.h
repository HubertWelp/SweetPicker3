#ifndef SORTENORTER_H
#define SORTENORTER_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QString>

class SortenOrter : public QWidget
{
    Q_OBJECT
public:
    explicit SortenOrter(QString bildPfad,QString bildName);
    void gebeKoordinatenein(int x1, int y1, int x2, int y2);

signals:

public slots:
    void zeichne();

private:
    QImage bild;
    QColor farbe;
    QString pfad;
    int o_x;
    int o_y;
    int u_x;
    int u_y;
};

#endif // SORTENORTER_H
