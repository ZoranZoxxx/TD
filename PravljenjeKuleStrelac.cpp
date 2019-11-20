#include "PravljenjeKuleStrelac.h"
#include "Igra.h"
#include "KulaStrelac.h"

extern Igra * igra;

PravljenjeKuleStrelac::PravljenjeKuleStrelac(QGraphicsItem *roditelj): QGraphicsPixmapItem(roditelj){
    setPixmap(QPixmap(":/slike/slike/strelac/shooting e0000.png"));
}

void PravljenjeKuleStrelac::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if (!igra->gradnja && igra->rezimPauze != 1){
        if(igra->zlato->getZlato() < 6)
            {
                QString p = QString(" Nemate zlata!");
                igra->poruka->novaPoruka(p);
                return;
             }
        igra->zlato->smanjiZlato(6);
        igra->poruka->izbrisiPoruku();
        igra->gradnja = new KulaStrelac(igra->brojacKula);
        igra->podesiKursor(QString(":/slike/slike/strelac/shooting e0000.png"));
    }
}

