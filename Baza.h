#ifndef BAZA
#define BAZA

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QGraphicsItem>

class Baza: public QGraphicsPixmapItem {
public:
    Baza(QPointF poz, QGraphicsItem * roditelj=0);
    QPointF vratiPoziciju();
private:
    QPointF pozicija;
};


#endif // BAZA

