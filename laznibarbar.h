#ifndef LAZNIBARBAR
#define LAZNIBARBAR

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include "laznineprijatelj.h"
#include <QMediaPlayer>

class LazniBarbar: public LazniNeprijatelj{
    Q_OBJECT
public:
    LazniBarbar(QList<QPointF> nizTacaka, int brZivota, int id, QGraphicsItem * roditelj=0);
    void rotirajPremaTacki(QPointF p);

    int tipNeprijatelja;

public slots:
    void pomeriNapred();
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
    int pocetniBrojZivota;//m
    QGraphicsRectItem* heltBar1;//m
    QGraphicsRectItem* heltBar2;//m
    QMediaPlayer * zvukSmrti;
    int id;
};

#endif // LAZNIBARBAR

