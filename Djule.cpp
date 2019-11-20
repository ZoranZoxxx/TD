#include "Djule.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Neprijatelj.h"
#include "Igra.h"
#include <QDebug>

extern Igra * igra;

Djule::Djule(QGraphicsItem *roditelj,double maksDomet): QObject(),QGraphicsPixmapItem(roditelj){//m
    setPixmap(QPixmap(":/slike/slike/djule/Imported piskel.png"));

    QTimer * tajmer = new QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(pomeri()));
    tajmer->start(25);

    maksimalniDomet = maksDomet;
    predjeniPut = 0;
}

void Djule::pomeri(){

    if (igra->rezimPauze != 1) {

        QList<QGraphicsItem *> pogoci = this->collidingItems();
        for(size_t i = 0, n = pogoci.size(); i < n; ++i){
            Neprijatelj * neprijatelj = dynamic_cast<Neprijatelj *>(pogoci[i]);

            if(neprijatelj)
            {
                neprijatelj->setBrojZivota(neprijatelj->getBrojZivota()-1);
                igra->scene()->removeItem(this);
                delete this;
                return;
            }
        }


        int POMERAJ = 30;
        double ugao = rotation();

        double dy = POMERAJ * qSin(qDegreesToRadians(ugao));
        double dx = POMERAJ * qCos(qDegreesToRadians(ugao));

        predjeniPut = predjeniPut + POMERAJ;
        if(predjeniPut >= maksimalniDomet)
        {

            igra->scene()->removeItem(this);
            delete this;

            return;
        }

        setPos(x()+dx, y()+dy);

    }

}

double Djule::vratiMaksimalniDomet(){
    return maksimalniDomet;
}

double Djule::vratiPredjeniPut(){
    return predjeniPut;
}

void Djule::postaviMaksimalniDomet(double duzina){
    maksimalniDomet = duzina;
}

void Djule::postaviPredjeniPut(double duzina){
    predjeniPut = duzina;
}
