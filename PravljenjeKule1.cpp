#include "PravljenjeKule1.h"
#include "Igra.h"
#include "Kula1.h"

extern Igra * igra;

PravljenjeKule1::PravljenjeKule1(QGraphicsItem *roditelj): QGraphicsPixmapItem(roditelj){
    setPixmap(QPixmap(":/slike/slike/spear catapult/shooting e0000.png"));
}

void PravljenjeKule1::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!igra->gradnja && igra->rezimPauze != 1){
        if(igra->zlato->getZlato() < 2)
        {
            QString p = QString(" Nemate zlata!");
            igra->poruka->novaPoruka(p);
            return;
        }
        igra->zlato->smanjiZlato(2);
        igra->poruka->izbrisiPoruku();
        (igra->brojacKula)++;
        igra->gradnja = new Kula1(igra->brojacKula);
        igra->podesiKursor(QString(":/slike/slike/spear catapult/shooting e0000.png"));
    }
}
