#include "LazniProjektil.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Neprijatelj.h"
#include "Igra.h"

extern Igra * igra;

LazniProjektil::LazniProjektil(QGraphicsItem *roditelj): QObject(),QGraphicsPixmapItem(roditelj){//m
    setPixmap(QPixmap(":/1/m1.png"));

    QTimer * tajmer = new QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(pomeri()));
    tajmer->start(25);
}

void LazniProjektil::pomeri(){

    if (igra->rezimPauze != 1) {
        int POMERAJ = 30;
        double ugao = rotation();

        double dy = POMERAJ * qSin(qDegreesToRadians(ugao));
        double dx = POMERAJ * qCos(qDegreesToRadians(ugao));

        setPos(x()+dx, y()+dy);

        samounistenje--;
        if(samounistenje < 0)
            delete this;
    }
}
