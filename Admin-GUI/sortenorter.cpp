#include "sortenorter.h"

SortenOrter::SortenOrter(QString bildPfad)
{
    pfad = bildPfad;
    farbe = QColor(0,255,255);
    bild = QPixmap(bildPfad);
}

void SortenOrter::gebeKoordinatenein(int x1, int y1, int x2, int y2)
{
    o_x = x1;
    u_x = x2;
    o_y = y1;
    u_y = y2;
}

QPixmap SortenOrter::zeichne()
{
    QPainter stift(&bild);
    stift.setPen(QPen(farbe,3));
    stift.drawRect(o_x,o_y,u_x-o_x,u_y-o_x);
    update();

    return bild;
}
