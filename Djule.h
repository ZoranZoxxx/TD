#ifndef DJULE_H
#define DJULE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Djule: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Djule(QGraphicsItem * roditelj=0,double maksimalniDomet=0);
public slots:
    virtual void pomeri();//m
    double vratiMaksimalniDomet();
    double vratiPredjeniPut();
    void postaviMaksimalniDomet(double duzina);
    void postaviPredjeniPut(double duzina);
private:
    double maksimalniDomet;
    double predjeniPut;
};

#endif // DJULE_H

