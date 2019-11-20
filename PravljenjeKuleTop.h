#ifndef PRAVLJENJEKULETOP_H
#define PRAVLJENJEKULETOP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class PravljenjeKuleTop: public QGraphicsPixmapItem{
public:
    PravljenjeKuleTop(QGraphicsItem* roditelj=0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PRAVLJENJEKULETOP_H

