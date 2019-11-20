#include "Projektil.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Neprijatelj.h"
#include "Igra.h"
#include <QDebug>

extern Igra * igra;

Projektil::Projektil(int id, double maksDomet, int tip, QGraphicsItem *roditelj): QObject(),QGraphicsPixmapItem(roditelj){//m
    if(tip == 0)
        setPixmap(QPixmap(":/1/m1.png"));
    else if(tip==1)
        setPixmap(QPixmap(":/slike/slike/djule/Imported piskel.png"));

    this->id = id;

    QTimer * tajmer = new QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(pomeri()));
    tajmer->start(25);

    maksimalniDomet = maksDomet;
    predjeniPut = 0;
    tipProjektila = tip;
}

void Projektil::pomeri(){

    if (igra->rezimPauze != 1) {

        QList<QGraphicsItem *> pogoci = this->collidingItems();
        for(size_t i = 0, n = pogoci.size(); i < n; ++i){
            Neprijatelj * neprijatelj = dynamic_cast<Neprijatelj *>(pogoci[i]);

            if(neprijatelj)
            {
                neprijatelj->setBrojZivota(neprijatelj->getBrojZivota()-1);

                if(igra->server->imaKorisnika()) {
                    igra->server->soket->write("menjanjeBrojaZivota");
                    igra->server->soket->write(" ");
                    igra->server->soket->write(std::to_string(neprijatelj->getId()).c_str());
                    igra->server->soket->write(" ");
                    igra->server->soket->write(std::to_string(neprijatelj->getBrojZivota()).c_str());
                    igra->server->soket->write(" ");
                    igra->server->soket->write(std::to_string(this->getID()).c_str());
                    igra->server->soket->write(" ");
                    igra->server->soket->write("objekat_kraj");
                    igra->server->soket->flush();
                    igra->server->soket->waitForBytesWritten(1000);
                }

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

double Projektil::vratiMaksimalniDomet(){
    return maksimalniDomet;
}

double Projektil::vratiPredjeniPut(){
    return predjeniPut;
}

void Projektil::postaviMaksimalniDomet(double duzina){
    maksimalniDomet = duzina;
}

void Projektil::postaviPredjeniPut(double duzina){
    predjeniPut = duzina;
}

int Projektil::getID() {
    return id;
}

int Projektil::vratiTipProjektila()
{
    return tipProjektila;
}

void Projektil::postaviTipProjektila(int n)
{
    tipProjektila = n;
}
