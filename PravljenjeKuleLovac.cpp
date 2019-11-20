#include "PravljenjeKuleLovac.h"
#include "Igra.h"
#include "KulaLovac.h"

extern Igra * igra;

PravljenjeKuleLovac::PravljenjeKuleLovac(QGraphicsItem *roditelj): QGraphicsPixmapItem(roditelj){
    setPixmap(QPixmap(":/1/slike/hunter/shooting e0000.png"));
}

void PravljenjeKuleLovac::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!igra->gradnja && igra->rezimPauze != 1){
        if(igra->zlato->getZlato() < 4)
        {
            QString p = QString(" Nemate zlata!");
            igra->poruka->novaPoruka(p);
            return;
        }
        igra->zlato->smanjiZlato(4);
        igra->poruka->izbrisiPoruku();
        igra->gradnja = new KulaLovac(igra->brojacKula);
        igra->podesiKursor(QString(":/1/slike/hunter/shooting e0000.png"));
    }
}

