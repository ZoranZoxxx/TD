#ifndef PRAVLJENJEKULESTRELAC_H
#define PRAVLJENJEKULESTRELAC_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class PravljenjeKuleStrelac: public QGraphicsPixmapItem{
public:
    PravljenjeKuleStrelac(QGraphicsItem* roditelj=0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PRAVLJENJEKULESTRELAC_H
