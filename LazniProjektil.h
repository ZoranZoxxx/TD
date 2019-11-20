#ifndef LAZNIPROJEKTIL_H
#define LAZNIPROJEKTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class LazniProjektil: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    LazniProjektil(QGraphicsItem * roditelj=0);

public slots:
    void pomeri();

private:
    int samounistenje = 3;
};

#endif // LAZNIPROJEKTIL_H
