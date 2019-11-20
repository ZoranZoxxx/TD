#ifndef BARBARIAN_KING_H
#define BARBARIAN_KING_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include "Neprijatelj.h"
#include <QMediaPlayer>
#include <QTimer>

class Barbarian_King: public Neprijatelj{
    Q_OBJECT
public:
    Barbarian_King(QList<QPointF> nizTacaka, int brZivota, int id, QGraphicsItem * roditelj=0);

    void rotirajPremaTacki(QPointF p);

    int tipNeprijatelja;//m
    QTimer * tajmerSinhronizacije;

public slots:
    void pomeriNapred();
    void sinhronizacija();

private:
    QList<QPointF> tacke;
    QPointF destinacija;
    int indeks;
    QString matricaKretanje[8][9];

    int SIRINA_POLJA_MREZE;
    int POLOVINA_SIRINE_POLJA_MREZE;
    int POLOVINA_SIRINE_SLICICE;

    int redniBrojKretanje;
    int BROJ_SMEROVA;
    int BROJ_SIMULACIJA_KRETANJE;
    int trenutniBrojZivota;
    int pocetniBrojZivota;
    QGraphicsRectItem* heltBar1;
    QGraphicsRectItem* heltBar2;
    QMediaPlayer * zvukSmrti;
};

#endif // BARBARIAN_KING_H
