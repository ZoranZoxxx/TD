#include "Kula.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Projektil.h"
#include <QPointF>
#include <QLineF>
#include "Igra.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include "Neprijatelj.h"

extern Igra * igra;

#include <QDebug>
Kula::Kula(int id/*MZ*/, QGraphicsItem *roditelj):QObject(), QGraphicsPixmapItem(roditelj){

}

double Kula::rastojanje(QGraphicsItem *objekat){
    QLineF ln(this->pos(),objekat->pos());
    return ln.length();
}

int Kula::getPrecnikDometa(){}

int Kula::getPolovinaSirine(){}

void Kula::pucaj(){

}

// MZ
int Kula::getId()
{
    return id;
}
// KRAJ

void Kula::pronadjiMetu(){

}


QGraphicsEllipseItem *Kula::getDomet(){}

int Kula::identifikacijaKula(){

}

int Kula::vratiX()
{
    return xm;
}

int Kula::vratiY()
{
    return ym;
}

void Kula::postaviX(int x1)
{
    xm = x1;
}

void Kula::postaviY(int y1)
{
    ym = y1;
}
