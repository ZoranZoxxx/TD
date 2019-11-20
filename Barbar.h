#ifndef BARBAR_H
#define BARBAR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include "Neprijatelj.h"
#include <QMediaPlayer>
#include <QTimer>

class Barbar: public Neprijatelj{
    Q_OBJECT
public:
    Barbar(QList<QPointF> nizTacaka, int brZivota, int id, QGraphicsItem * roditelj=0);
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
    QString matricaKretanje[8][8];

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

#endif // BARBAR_H
