#include "sortenorter.h"

SortenOrter::SortenOrter(QString bildPfad, int r, int g, int b)
{
    pfad = bildPfad;
    farbe = QColor(r,g,b);
    bild = QPixmap(bildPfad);
}

QPixmap SortenOrter::zeichne(int o_x, int o_y, int u_x, int u_y)
{
    QPainter stift(&bild);
    stift.setPen(QPen(farbe,3));
    stift.drawRect(o_x,o_y,u_x-o_x,u_y-o_x);
    update();

    return bild;
}
