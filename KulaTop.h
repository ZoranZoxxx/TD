#ifndef KULATOP_H
#define KULATOP_H

#include "Kula.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QWidget>

class KulaTop: public Kula{
    Q_OBJECT
public:
    KulaTop(int id, QGraphicsItem * roditelj=0);
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
    int BR_SIMULACIJA_GADJANJA = 9;
    int redniBroj = 0;
    QString matricaSlika[8][9];
    QTimer *tajmer = new QTimer(this);
    QTimer *tajmer2 = new QTimer(this);
};

#endif // KULATOP_H

