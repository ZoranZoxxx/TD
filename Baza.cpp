#include "Igra.h"
#include "Baza.h"

extern Igra * igra;

Baza::Baza(QPointF poz, QGraphicsItem * roditelj):QGraphicsPixmapItem(roditelj)
{
    pozicija = poz;
    setPixmap(QPixmap(QString(":/1/baza.png")));
}

QPointF Baza::vratiPoziciju()
{
    return pozicija;
}

