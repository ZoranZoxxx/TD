#ifndef NEPRIJATELJ_H
#define NEPRIJATELJ_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>

class Neprijatelj: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Neprijatelj(QList<QPointF> nizTacaka, int brZivota, int id /*MARIJA*/, QGraphicsItem * roditelj=0);

    virtual ~Neprijatelj()
    {}

    int getId();
    int getBrojZivota();
    void setBrojZivota(int b);

private:
    QList<QPointF> tacke;
    int BrojZivota;

protected:
    int id;

};

#endif // NEPRIJATELJ_H
