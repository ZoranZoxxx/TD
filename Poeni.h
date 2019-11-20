#ifndef POENI_H
#define POENI_H

#include <QGraphicsTextItem>
#include <QTimer>

class Poeni: public QGraphicsTextItem
{
    //Q_OBJECT
public:
    Poeni(QGraphicsItem *parent = 0,QString resurs= QString(""));
    void povecajPoene();
    void povecajZlato(int z);
    void smanjiZlato(int s);
    void smanjiZivotBaze();
    void novaPoruka(QString p);
    int getPoeni();
    int getZlato();
    int getZivotBaze();
    void povecajNivo();

public slots:
    void izbrisiPoruku();

private:
    int poeni;
    int zlato;
    int zivotBaze;
    QString poruka;
    QTimer * tajmer5;
};

#endif // POENI_H


