#include "dugme.h"

Dugme::Dugme(QPixmap slika, int x, int y, QPushButton *roditelj):QPushButton(roditelj)
{
    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    brush->setTexture(slika);
    palette->setBrush(QPalette::Button,*(brush));
    setFlat(true);
    setAutoFillBackground(true);
    setPalette(*palette);
    setMask(slika.mask());
    setFixedSize(slika.width(), slika.height());
    move(x, y);
}



