#ifndef PROJEKTIL_H
#define PROJEKTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Projektil: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Projektil(int id, double maksimalniDomet=0, int tip=0, QGraphicsItem * roditelj=0);
public slots:
    void pomeri();
    double vratiMaksimalniDomet();
    double vratiPredjeniPut();
    void postaviMaksimalniDomet(double duzina);
    void postaviPredjeniPut(double duzina);
    int getID();
    int vratiTipProjektila();
    void postaviTipProjektila(int n);
private:
    double maksimalniDomet;
    double predjeniPut;
    int id;
    int tipProjektila;
    QGraphicsEllipseItem* centarPogotka;
};

#endif // PROJEKTIL_H
