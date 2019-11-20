#ifndef LAZNINEPRIJATELJ
#define LAZNINEPRIJATELJ

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>

class LazniNeprijatelj: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    LazniNeprijatelj(QList<QPointF> nizTacaka, int brZivota, QGraphicsItem * roditelj=0);
    virtual ~LazniNeprijatelj() {}
    int getBrojZivota();
    void setBrojZivota(int b);

private:
    QList<QPointF> tacke;
    int BrojZivota;
};


#endif // LAZNINEPRIJATELJ

