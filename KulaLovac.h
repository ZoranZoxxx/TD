#ifndef KULALOVAC_H
#define KULALOVAC_H

#include "Kula.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QWidget>

class KulaLovac: public Kula{
    Q_OBJECT
public:
    KulaLovac(int id, QGraphicsItem * roditelj=0);
    int identifikacijaKula();
    QMediaPlayer * zvukStrele;

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
    int BR_SIMULACIJA_GADJANJA = 13;
    int redniBroj = 0;
    QString matricaSlika[8][13];
    QTimer *tajmer = new QTimer(this);
    QTimer *tajmer2 = new QTimer(this);
};


#endif // KULALOVAC_H
