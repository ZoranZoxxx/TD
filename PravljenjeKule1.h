#ifndef PRAVLJENJEKULE1_H
#define PRAVLJENJEKULE1_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class PravljenjeKule1: public QGraphicsPixmapItem{
public:
    PravljenjeKule1(QGraphicsItem* roditelj=0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PRAVLJENJEKULE1_H
