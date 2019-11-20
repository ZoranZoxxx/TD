#include "PravljenjeKuleTop.h"
#include "Igra.h"
#include "KulaTop.h"

extern Igra * igra;

PravljenjeKuleTop::PravljenjeKuleTop(QGraphicsItem *roditelj): QGraphicsPixmapItem(roditelj){
    setPixmap(QPixmap(":/slike/slike/top/schuss e0000.png"));
}

void PravljenjeKuleTop::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!igra->gradnja && igra->rezimPauze != 1){
        if(igra->zlato->getZlato() < 8)
        {
            QString p = QString(" Nemate zlata!");
            igra->poruka->novaPoruka(p);
            return;
        }
        igra->zlato->smanjiZlato(8);
        igra->poruka->izbrisiPoruku();
        igra->gradnja = new KulaTop(igra->brojacKula);
        igra->podesiKursor(QString(":/slike/slike/top/schuss e0000.png"));
    }
}

