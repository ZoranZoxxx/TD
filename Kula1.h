#ifndef KULA1_H
#define KULA1_H

#include "Kula.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QWidget>

class Kula1: public Kula{
    Q_OBJECT
public:
    Kula1(int id, QGraphicsItem * roditelj=0);
    int identifikacijaKula();
    QMediaPlayer * zvukStrele;
    QString matricaSlika[8][9]; // JA PROMENILA !!!
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    int getPrecnikDometa();
    int getPolovinaSirine();
    QGraphicsEllipseItem * getDomet();

public slots:
    void pronadjiMetu();
    void pucaj();

private:
    int PRECNIK_KRUGA_DOMETA;
    int POLOVINA_SIRINE_KULE;
    QGraphicsEllipseItem * domet;
    QPointF meta;
    bool metaPronadjena;
    int BROJ_SMEROVA = 8;
    int BR_SIMULACIJA_GADJANJA = 9;
    int redniBroj = 0;
    QTimer *tajmer = new QTimer(this);
    QTimer *tajmer2 = new QTimer(this);
};

#endif // KULA1_H
