#include "laznineprijatelj.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Igra.h"
#include <QDebug>

extern Igra* igra;

LazniNeprijatelj::LazniNeprijatelj(QList<QPointF> nizTacaka, int brZivota, QGraphicsItem *roditelj){
    this->BrojZivota = brZivota;
    tacke = nizTacaka;
    QTimer * tajmer = new QTimer(this);
}

int LazniNeprijatelj::getBrojZivota() {
    return BrojZivota;
}

void LazniNeprijatelj::setBrojZivota(int b) {
    this->BrojZivota = b;
}
