#ifndef LAZNAKULA1_H
#define LAZNAKULA1_H

#include "LaznaKula.h"

class LaznaKula1: public LaznaKula{
    Q_OBJECT
public:
    LaznaKula1(QPointF pozicija, int id, QGraphicsItem * roditelj=0);
    //int identifikacijaKula();//m
    QMediaPlayer * zvukStrele;
    QString matricaSlika[8][9]; // JA PROMENILA !!!

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


#endif // LAZNAKULA1

