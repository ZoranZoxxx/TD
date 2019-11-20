//#include "LaznaKula.h"
//#include <QPixmap>
//#include <QTimer>
//#include <qmath.h>
//#include "Igra.h"
//#include <QDebug>

//extern Igra* igra;

//LaznaKula::LaznaKula(QString nazivSlike, QPointF koordinate, int rotacija, int redniBroj){
//    this->nazivSlike = nazivSlike;
//    this->koordinate = koordinate;
//    this->rotacija = rotacija;
//    this->redniBroj = redniBroj;

//    this->setPixmap(QPixmap(nazivSlike));
//    this->setPos(koordinate);

//}

//QString LaznaKula::getNazivSlike() {
//    return nazivSlike;
//}

//void LaznaKula::setNazivSlike(QString niska) {
//    this->nazivSlike = niska;
//}

//QPointF LaznaKula::getKoordinate() {
//    return koordinate;
//}

//void LaznaKula::setKoordinate(QPointF tacka) {
//    this->koordinate = tacka;
//}

//int LaznaKula::getRotacija() {
//    return rotacija;
//}

//void LaznaKula::setRotacija(int rotacija) {
//    this->rotacija = rotacija;
//}

//int LaznaKula::getRedniBroj() {
//    return redniBroj;
//}

//void LaznaKula::setRedniBroj(int redniBroj) {
//    this->redniBroj = redniBroj;
//}


#include "LaznaKula.h"
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
LaznaKula::LaznaKula(QPointF pozicija, int id/*MZ*/, QGraphicsItem *roditelj):QObject(), QGraphicsPixmapItem(roditelj){

}

double LaznaKula::rastojanje(QGraphicsItem *objekat){
    QLineF ln(this->pos(),objekat->pos());
    return ln.length();
}

void LaznaKula::pucaj(){

}

// MZ
int LaznaKula::getId()
{
    return id;
}
// KRAJ

void LaznaKula::pronadjiMetu(){

}


//QGraphicsPolygonItem getDomet(){

//}

//int LaznaKula::identifikacijaKula(){//m

//}//m

int LaznaKula::vratiX()//m
{
    return xm;//m
}

int LaznaKula::vratiY()//m
{
    return ym;//m
}

void LaznaKula::postaviX(int x1)//m
{
    xm = x1;//m
}

void LaznaKula::postaviY(int y1)//m
{
    ym = y1;//m
}

