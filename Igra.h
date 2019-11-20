#ifndef IGRA_H
#define IGRA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "Kula.h"
#include "Polje.h"
#include "Poeni.h"
#include <QPushButton>
#include "dugme.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include "Server.h"
#include "Klijent.h"
#include "LaznaKula.h"
#include "laznineprijatelj.h"
#include "LazniProjektil.h"
#include "Neprijatelj.h"
#include <QButtonGroup> // MZ
#include <QRadioButton> // MZ
#include <QTime>

class Igra: public QGraphicsView{
    Q_OBJECT
public:
    Igra();
    void podesiKursor(QString niska);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void stvoriBarbarian_Kraljeve(int brojNeprijatelja, int naKolikoSekindi);
    void stvoriBarbare(int brojNeprijatelja, int naKolikoSekindi);
    void stvoriPut();
    void keyPressEvent(QKeyEvent * event);
    void pokreniGlavniMeni();
    void pauza();
    void krajIgre();
    void mouseDoubleClickEvent(QMouseEvent *event);
    float skaliranjePoX;
    float skaliranjePoY;
    void stvoriOrke(int brojNeprijatelja, int naKolikoSekindi);

    QGraphicsScene * scena;
    QGraphicsPixmapItem * kursor;
    QGraphicsEllipseItem * domet;//zz
    Kula * gradnja;
    QTimer * tajmerKreiranjaBarbarian_Kraljeva;
    int brojKreiranihBarbarian_Kraljeva;
    int maksimalniBrojBarbarian_Kraljeva;
    QTimer * tajmerKreiranjaBarbara;
    int brojKreiranihBarbara;
    int maksimalniBrojBarbara;
    QTimer * tajmerKreiranjaOrka;
    int brojKreiranihOrka;
    int maksimalniBrojOrka;
    Poeni *porukaNivo;
    QList<QPointF> putanjaKretanja;
    QList<Kula*> listaKula;
    Poeni *poeni;
    Poeni *zlato;
    Poeni *zivotBaze;
    Poeni *poruka;
    Dugme * btnZapocni;
    Dugme * btnPrikljuciSe;
    Dugme * btnOpcije;
    Dugme * btnPravila;
    Dugme * btnIzlaz;
    Dugme * btnIgra;
    Dugme * btnMeni;
    Dugme * btnOpcijeP;
    Dugme * btnMeni2;
    Dugme * btnPovratak;
    QGraphicsPixmapItem * pravougaonik;
    QGraphicsPixmapItem * pravougaonik2;
    QGraphicsPixmapItem * pauzaLogo;
    QGraphicsPixmapItem * logoKraj;
    QGraphicsTextItem * tekst1;
    QGraphicsTextItem * tekst2;
    int rezim;
    int rezimPauze;
    int rezimOpcija;
    int kraj;
    QPushButton* prodaja;
    Kula* kulaZaProdaju;
    int rezimProdaja;
    int proveraPuta(int x, int y);
    QButtonGroup * fullscreen;
    QRadioButton * rb1;
    QRadioButton * rb2;
    QMediaPlaylist * plejlista;
    QMediaPlayer * plejer;
    QSlider * jacinaZvuka;
    LaznaKula * nizLaznihKula[1000];
    Neprijatelj * nizNeprijatelja[1000];
    LazniNeprijatelj * nizLaznihNeprijatelja[1000];
    LazniProjektil * nizLaznihProjektila[1000];
    int brojacKula;
    int brojacNeprijatelja;
    int brojacProjektila;
    Server *server;
    QTimer* tajmerZaBrisanjeProdaje;
    QTimer* tajmerZaNivo;
    QTime t;
    int protekloMilisekundi = 0;
    int milisekundeZaNivo;
    int nivo;
    int brojNivoa;
    int brojBarbaraUNivou;
    int brojBarbarianKingovaUNivou;
    int brojOrkovaUNivou;
    int brojNeprijateljaUNivou;
    void rotiranjeKuleKodKlijenta(int id, QPointF meta, int redniBroj);  // MZ

public slots:
    void stvoriJednogBarbarian_Kralja();
    void stvoriJednogBarbara();
    void stvoriJednogOrka();
    void pokreniIgru();
    void prikljuciSeIgri();
    void opcije();
    void izlaz();
    void povratakUIgru();
    void povratakNaMeni();
    void prodajKulu();
    void podesiJacinu();
    void vratiSe();
    void putZaKlijenta();
    void objekatZaKlijenta();
    void porukaZaServer();
    void ceoEkran();
    void prozor();
    void brisanjeProdaje();
    void pokreniNivo();

private:
    bool modCelogEkrana;
    Polje ***matrica;
    int BR_POLJA_PO_SIRINI;
    int BR_POLJA_PO_VISINI;
    int SIRINA_POLJA_MREZE;
    int POLOVINA_SIRINE;
    int SIRINA_PROZORA;
    int VISINA_PROZORA;
    int SIRINA_DUGMETA;
    int VISINA_DUGMETA;
    int RAZMAK;
    int pozicijaPesme;
    Klijent *klijent;

};

#endif // IGRA_H
