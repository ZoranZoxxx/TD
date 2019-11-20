#ifndef KULA_H
#define KULA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class Kula:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Kula(int id/*MZ*/, QGraphicsItem * roditelj=0);
    double rastojanje(QGraphicsItem * objekat);
    virtual void pucaj();
    int getId();
    virtual int getPrecnikDometa();
    virtual int getPolovinaSirine();
    virtual QGraphicsEllipseItem * getDomet();

public slots:
    virtual void pronadjiMetu();
    virtual int identifikacijaKula();
    int vratiX();
    int vratiY();
    void postaviX(int x1);
    void postaviY(int y1);
private:
    int xm;
    int ym;
protected:
    int id;

};

#endif // KULA_H
