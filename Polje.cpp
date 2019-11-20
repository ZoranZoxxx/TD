#include "Polje.h"
#include "Igra.h"

extern Igra * igra;


Polje::Polje(int _x, int _y, QGraphicsItem *roditelj): QGraphicsPixmapItem(roditelj){
    x = _x;
    y = _y;
    setPixmap(QPixmap(":/1/pozadina.png"));
    setPos(x, y);
    dodatak = new QGraphicsPixmapItem();
    dodatak->setPos(x, y);
}

Polje::~Polje(){

}

void Polje::postaviPut(bool vrednost){
    jePut = vrednost;
}

bool Polje::vratiPut(){
    return jePut;
}

void Polje::postaviKulu(bool vrednost){
    jeKula = vrednost;
}

bool Polje::vratiKulu(){
    return jeKula;
}


bool Polje::getZauzeto(){
    return _zauzetoPolje;
}

void Polje::setZauzeto(bool vrednost)
{
    _zauzetoPolje = vrednost;
}
