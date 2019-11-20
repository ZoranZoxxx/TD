#ifndef PRAVLJENJEKULELOVAC_H
#define PRAVLJENJEKULELOVAC_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class PravljenjeKuleLovac: public QGraphicsPixmapItem{
public:
    PravljenjeKuleLovac(QGraphicsItem* roditelj=0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PRAVLJENJEKULELOVAC_H
