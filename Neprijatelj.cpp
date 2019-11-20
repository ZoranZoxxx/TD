#include "Neprijatelj.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Igra.h"
#include <QDebug>

extern Igra* igra;

Neprijatelj::Neprijatelj(QList<QPointF> nizTacaka, int brZivota, int id, QGraphicsItem *roditelj){
    this->BrojZivota = brZivota;
    tacke = nizTacaka;

    QTimer * tajmer = new QTimer(this);
}

int Neprijatelj::getId() {
    return id;
}

int Neprijatelj::getBrojZivota() {
    return BrojZivota;
}

void Neprijatelj::setBrojZivota(int b) {
    this->BrojZivota = b;
}
