#ifndef POLJE_H
#define POLJE_H

#include <QGraphicsPixmapItem>

class Polje: public QGraphicsPixmapItem{
private:
    int x;
    int y;
    bool jePut;
    bool jeKula;
    bool _zauzetoPolje;

public:
    Polje(int x, int y, QGraphicsItem *roditelj = 0);
    ~Polje();


    QGraphicsPixmapItem *dodatak;
    void postaviPut(bool vrednost);
    bool vratiPut();
    void postaviKulu(bool vrednost);
    bool vratiKulu();
    bool getZauzeto();
    void setZauzeto(bool vrednost);

};

#endif // POLJE_H
