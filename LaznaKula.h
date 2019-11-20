//#ifndef LAZNIOBJEKAT
//#define LAZNIOBJEKAT


//#include <QGraphicsPixmapItem>
//#include <QObject>
//#include <QList>
//#include <QPointF>

//class LaznaKula: public QObject, public QGraphicsPixmapItem{
//    Q_OBJECT
//public:
//    LaznaKula(QString nazivSlike, QPointF koordinate, int rotacija, int redniBroj);

//    virtual ~LaznaKula()
//    {}

//    QString getNazivSlike();
//    void setNazivSlike(QString niska);
//    QPointF getKoordinate();
//    void setKoordinate(QPointF tacka);
//    int getRotacija();
//    void setRotacija(int rotacija);
//    int getRedniBroj();
//    void setRedniBroj(int redniBroj);

//    int POLOVINA_SIRINE_KULE = 48;  // MZ
//    QString matricaSlika[8][9]; // MZ

//private:
//    QString nazivSlike;
//    QPointF koordinate;
//    int rotacija;
//    int redniBroj;
//};



//#endif // LAZNIOBJEKAT

#ifndef LAZNAKULA_H
#define LAZNAKULA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class LaznaKula:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    LaznaKula(QPointF pozicija, int id/*MZ*/, QGraphicsItem * roditelj=0);
    double rastojanje(QGraphicsItem * objekat);
    virtual void pucaj();
    int getId();    //MZ
public slots:
    virtual void pronadjiMetu();
//    virtual int identifikacijaKula();//m
    int vratiX();
    int vratiY();
    void postaviX(int x1);
    void postaviY(int y1);
private: //m
    int xm;//m
    int ym;//m
protected:
    int id; // MZ
    int pozicija;   //MZ

};

#endif // LAZNAKULA_H


