#include "Igra.h"
#include <QGraphicsScene>
#include "Kula1.h"
#include "Projektil.h"
#include "Neprijatelj.h"
#include "Barbarian_King.h"
#include "Ork.h"
#include "Barbar.h"
#include "PravljenjeKule1.h"
#include "PravljenjeKuleLovac.h"
#include "PravljenjeKuleStrelac.h"
#include "PravljenjeKuleTop.h"
#include <QTimer>
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsLineItem>
#include <QGraphicsColorizeEffect>
#include <QTime>
#include <Baza.h>
#include <Slucajnaputanja.h>
#include <QPixmap>
#include <QKeyEvent>
#include <QPushButton>
#include <QBitmap>
#include <QPainter>
#include <QImage>
#include <QDesktopWidget>
#include <QFont>
#include <QDebug>
#include <QRadioButton>
#include <QHBoxLayout>
#include "LaznaKula.h"
#include "laznibarbar.h"
#include "laznibarbarianKing.h"
#include "lazniOrk.h"
#include "laznakula1.h"


Igra::Igra(): QGraphicsView(){
    scena = new QGraphicsScene(this);
    BR_POLJA_PO_SIRINI = 15;
    BR_POLJA_PO_VISINI = 10;
    SIRINA_POLJA_MREZE = 96;
    POLOVINA_SIRINE = 48;
    SIRINA_PROZORA = SIRINA_POLJA_MREZE*15;
    VISINA_PROZORA = SIRINA_POLJA_MREZE*10;
    SIRINA_DUGMETA = 300;
    VISINA_DUGMETA = 70;
    RAZMAK = 30;
    nivo = 1;
    brojNivoa = 3;

    scena->setSceneRect(0,0,BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 200,BR_POLJA_PO_VISINI*SIRINA_POLJA_MREZE);

    setFixedSize(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 200,BR_POLJA_PO_VISINI*SIRINA_POLJA_MREZE);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    modCelogEkrana = true;

    // podesavanje rezolucije
    QDesktopWidget desktop;
    skaliranjePoX = (float) desktop.geometry().width() / (float) QGraphicsView::width();
    skaliranjePoY = (float) desktop.geometry().height() /  (float) QGraphicsView::height();

    QGraphicsView::scale(skaliranjePoX, skaliranjePoY);
    this->setWindowState(Qt::WindowFullScreen);

    setScene(scena);

    rezim = 0;
    rezimPauze = 0;
    rezimProdaja = 0;
    rezimOpcija = 0;
    kraj = 0;

    // namestanje plejliste
    plejlista = new QMediaPlaylist();

    plejlista->addMedia(QUrl("qrc:/1/melodijaMeni.mp3"));
    plejlista->addMedia(QUrl("qrc:/1/melodijaIgra.wav"));
    plejlista->addMedia(QUrl("qrc:/1/melodijaPauza.mp3"));

    plejer = new QMediaPlayer();
    plejer->setPlaylist(plejlista);
    plejer->setVolume(50);

    pokreniGlavniMeni();
}

void Igra::podesiKursor(QString putanja_do_fajla_slike){
    if (kursor){
        scena->removeItem(kursor);
        delete kursor;
    }
    kursor = new QGraphicsPixmapItem();
    kursor->setPixmap(QPixmap(putanja_do_fajla_slike));
    scena->addItem(kursor);

    int a = gradnja->getPrecnikDometa();
    int b = gradnja->getPrecnikDometa();;
    double polovina_a = a/2;
    double polovina_b = b/2;

    domet = new QGraphicsEllipseItem(-1*polovina_a + gradnja->getPolovinaSirine(), -1*polovina_b + gradnja->getPolovinaSirine(), a, b);
    domet->setBrush(Qt::green);
    domet->setOpacity(0.2);
    scena->addItem(domet);
}

void Igra::mouseMoveEvent(QMouseEvent *event){

    if((rezim == 1 || rezim == 2) && rezimPauze != 1) {
        if (kursor){
            int i = ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;
            int j = ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;

            if(i >= BR_POLJA_PO_SIRINI || j >= BR_POLJA_PO_VISINI){
                kursor->setPos((event->pos().x()-POLOVINA_SIRINE) / (modCelogEkrana ? skaliranjePoX : 1),
                               (event->pos().y()-POLOVINA_SIRINE) / (modCelogEkrana ? skaliranjePoY : 1));
                domet->setPos((event->pos().x()-POLOVINA_SIRINE) / (modCelogEkrana ? skaliranjePoX : 1),
                              (event->pos().y()-POLOVINA_SIRINE) / (modCelogEkrana ? skaliranjePoY : 1));
                domet->setBrush(Qt::red);
                return;
            }

            QGraphicsColorizeEffect *efekat = new QGraphicsColorizeEffect(this);

            if (matrica[i][j]->getZauzeto()==true){
                kursor->setOpacity(0.6);
                efekat->setColor(QColor(255, 0, 0));
                kursor->setGraphicsEffect(efekat);
                domet->setBrush(Qt::red);
            }
            else {
                kursor->setOpacity(0.6);
                efekat->setColor(QColor(0, 200, 0));
                kursor->setGraphicsEffect(efekat);
                domet->setBrush(Qt::green);
            }

            kursor->setPos((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE,
                           (int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE );
            domet->setPos((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE,
                          (int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE );
        }
    }
    else
        QGraphicsView::mouseMoveEvent(event);
}

void Igra::mousePressEvent(QMouseEvent *event){
    if (rezimPauze != 1) {
        if(rezim == 1) {
            int i = ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;
            int j = ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;

            if (gradnja){
                if(i >= BR_POLJA_PO_SIRINI || j >= BR_POLJA_PO_VISINI)
                    return;

                if (matrica[i][j]->getZauzeto() == true)
                    return;

                kursor->setOpacity(1);
                kursor->setGraphicsEffect(0);

                int gradnjaX = (int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE;
                int gradnjaY = (int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE;
                gradnja->setPos(gradnjaX, gradnjaY);
                delete domet;

                scena->addItem(gradnja);

                if(gradnjaX + 500 > 0 && gradnjaY + 500 > 0) {
                    if(server->imaKorisnika()) {
                        server->soket->write("gradnja_kule");
                        server->soket->write(" ");
                        server->soket->write((std::to_string(gradnjaX + 500).c_str()));
                        server->soket->write("-");
                        server->soket->write((std::to_string(gradnjaY + 500).c_str()));
                        server->soket->write(" ");
                        server->soket->write((std::to_string(((Kula1*)(gradnja))->getId()).c_str()));
                        server->soket->write(" ");
                        server->soket->write((std::to_string(i).c_str()));
                        server->soket->write("+");
                        server->soket->write((std::to_string(j).c_str()));
                        server->soket->write(" ");
                        server->soket->write(std::to_string(gradnja->identifikacijaKula()).c_str());
                        server->soket->write(" ");
                        server->soket->write("0");
                        server->soket->write(" ");
                        server->soket->waitForBytesWritten(1000);
                    }

                    if(server->imaKorisnika()) {
                        server->soket->write("objekat_kraj");
                        server->soket->flush();
                        server->soket->waitForBytesWritten(1000);
                    }
                }

                matrica[i][j]->setZauzeto(true);
                matrica[i][j]->postaviKulu(true);

                gradnja->postaviX(i);
                gradnja->postaviY(j);

                listaKula << gradnja;
                scena->removeItem(kursor);
                kursor = 0;
                gradnja = 0;
            }
            else {
                QGraphicsView::mousePressEvent(event);
            }
        }
        else if(rezim == 2) {
            int i = ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(event->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;
            int j = ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(event->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;

            if (gradnja){
                if(i >= BR_POLJA_PO_SIRINI || j >= BR_POLJA_PO_VISINI)
                    return;

                if (matrica[i][j]->getZauzeto() == true)
                    return;

                kursor->setOpacity(1);
                kursor->setGraphicsEffect(0);

                klijent->soket->write((std::to_string(i).c_str()));
                klijent->soket->write("-");
                klijent->soket->write((std::to_string(j).c_str()));
                klijent->soket->write(" ");
                klijent->soket->write((std::to_string(gradnja->identifikacijaKula()).c_str()));
                klijent->soket->write(" kraj_poruke");
                klijent->soket->flush();
                klijent->soket->waitForBytesWritten(1000);

                scena->removeItem(kursor);
                kursor = 0;
                gradnja = 0;
            }
            else {
                QGraphicsView::mousePressEvent(event);
            }
        }
        else {
            QGraphicsView::mousePressEvent(event);
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

void Igra::mouseDoubleClickEvent(QMouseEvent *e) {
    if(rezim==1 && rezimPauze!=1)
    {

        if(rezimProdaja)
        {
            prodaja->close();
            delete prodaja;
            rezimProdaja = 0;
            delete tajmerZaBrisanjeProdaje;
        }

        int i = ((int)(e->pos().x() / (modCelogEkrana ? skaliranjePoX : 1)) - ((int)(e->pos().x() / (modCelogEkrana ? skaliranjePoX : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;
        int j = ((int)(e->pos().y() / (modCelogEkrana ? skaliranjePoY : 1)) - ((int)(e->pos().y() / (modCelogEkrana ? skaliranjePoY : 1))) % SIRINA_POLJA_MREZE) / SIRINA_POLJA_MREZE;

        if(i >= BR_POLJA_PO_SIRINI || j >= BR_POLJA_PO_VISINI)
            return;
        if(matrica[i][j]->vratiKulu()==true)
        {
            for(int k=0;k<listaKula.size();k++)
            {
                if(listaKula[k]->vratiX() == i && listaKula[k]->vratiY() == j)
                {
                    kulaZaProdaju = listaKula[k];
                    prodaja = new QPushButton();
                    prodaja->setText("Prodaja");
                    prodaja->move(i*SIRINA_POLJA_MREZE+10,j*SIRINA_POLJA_MREZE-10);
                    rezimProdaja = 1;
                    scene()->addWidget(prodaja);
                    connect(prodaja,SIGNAL(clicked()),this,SLOT(prodajKulu()));
                    tajmerZaBrisanjeProdaje = new QTimer();
                    connect(tajmerZaBrisanjeProdaje,SIGNAL(timeout()),this,SLOT(brisanjeProdaje()));
                    tajmerZaBrisanjeProdaje->start(2000);
                    return;
                }
            }
        }
    }
}

void Igra::brisanjeProdaje()
{
    if(rezimProdaja ==1){
        prodaja->close();
        rezimProdaja = 0;
        delete tajmerZaBrisanjeProdaje;
    }
}

void Igra::prodajKulu()
{
    int i,j;
    i = kulaZaProdaju->vratiX();
    j = kulaZaProdaju->vratiY();
    matrica[i][j]->setZauzeto(false);
    matrica[i][j]->postaviKulu(false);
    switch(kulaZaProdaju->identifikacijaKula())
    {
    case 1:
        zlato->povecajZlato(1);
        break;
    case 2:
        zlato->povecajZlato(2);
        break;
    case 3:
        zlato->povecajZlato(3);
        break;
    case 4:
        zlato->povecajZlato(4);
        break;
    }
    scene()->removeItem(kulaZaProdaju);
    listaKula.removeOne(kulaZaProdaju);

    if(server->imaKorisnika()) {
        server->soket->write("prodaja_kule");
        server->soket->write(" ");
        server->soket->write(std::to_string(kulaZaProdaju->getId()).c_str());
        server->soket->write(" ");
        server->soket->write(std::to_string(kulaZaProdaju->identifikacijaKula()).c_str());
        server->soket->write(" ");
        server->soket->waitForBytesWritten(1000);
    }

    if(server->imaKorisnika()) {
        server->soket->write("objekat_kraj");
        server->soket->flush();
        server->soket->waitForBytesWritten(1000);
    }

    delete kulaZaProdaju;
    prodaja->close();
    rezimProdaja = 0;
    delete tajmerZaBrisanjeProdaje;
}

void Igra::podesiJacinu()
{
    plejer->setVolume(jacinaZvuka->value());
}

void Igra::vratiSe()
{
    rezimOpcija = 0;
    QTimer::singleShot(100, [this] () {

        if (rezimPauze == 1)
        {
            scena->removeItem(pravougaonik2);
            jacinaZvuka->close();
            btnPovratak->close();
            rb1->close();
            rb2->close();
            scena->removeItem(tekst1);
            scena->removeItem(tekst2);
        }
        else
        {
            scena->clear();
            pokreniGlavniMeni();
        }
    });
}

void Igra::putZaKlijenta() {
    QStringList put = klijent->vratiPoruku().split(" ");

    QStringList koordinate = put[0].split("-");
    putanjaKretanja << QPointF(atoi(koordinate[0].toStdString().c_str()) - 100 + SIRINA_POLJA_MREZE / 2,
            atoi(koordinate[1].toStdString().c_str()) * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2);
    for(int i = 0; i < put.size() - 1; i++) {
        QStringList koordinate = put[i].split("-");
        matrica[atoi(koordinate[0].toStdString().c_str())][atoi(koordinate[1].toStdString().c_str())]->setZauzeto(true);
        putanjaKretanja << QPointF(atoi(koordinate[0].toStdString().c_str()) * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2,
                atoi(koordinate[1].toStdString().c_str()) * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2);
    }
    for(int i = 0; i < put.size() - 2; i++) {
        QStringList koordinate = put[i].split("-");
        int pravac = proveraPuta(atoi(koordinate[0].toStdString().c_str()), atoi(koordinate[1].toStdString().c_str()));
        matrica[atoi(koordinate[0].toStdString().c_str())][atoi(koordinate[1].toStdString().c_str())]->dodatak->setPixmap(QPixmap(QString(":/put/slike/put/s%1.png").arg(pravac)));
        scena->addItem(matrica[atoi(koordinate[0].toStdString().c_str())][atoi(koordinate[1].toStdString().c_str())]->dodatak);
    }
    koordinate = put[put.size() - 2].split("-");
    matrica[atoi(koordinate[0].toStdString().c_str())][atoi(koordinate[1].toStdString().c_str())]->dodatak->setPixmap(QPixmap(QString(":/1/baza.png")));;
    scena->addItem(matrica[atoi(koordinate[0].toStdString().c_str())][atoi(koordinate[1].toStdString().c_str())]->dodatak);
}

void Igra::objekatZaKlijenta()
{
    QStringList lista = klijent->vratiPoruku().split(" ");
    QString niska = lista[0];

    if (niska.contains("napravi_Barbara"))
    {
        nizLaznihNeprijatelja[brojacNeprijatelja] = new LazniBarbar(putanjaKretanja, 5, brojacNeprijatelja, 0);
        nizLaznihNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
        scena->addItem(nizLaznihNeprijatelja[brojacNeprijatelja++]);
    }
    else if (niska.contains("napravi_Barbarian_Kinga"))
    {
        nizLaznihNeprijatelja[brojacNeprijatelja] = new LazniBarbarianKing(putanjaKretanja, 5, brojacNeprijatelja, 0);
        nizLaznihNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
        scena->addItem(nizLaznihNeprijatelja[brojacNeprijatelja++]);
    }
    else if (niska.contains("napravi_Orka"))
    {
        nizLaznihNeprijatelja[brojacNeprijatelja] = new LazniOrk(putanjaKretanja, 5, brojacNeprijatelja, 0);
        nizLaznihNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
        scena->addItem(nizLaznihNeprijatelja[brojacNeprijatelja++]);
    }

    else if (niska.contains("menjanjeBrojaZivota"))
    {
        int id = lista[1].toInt();
        int brojZivota = lista[2].toInt();
        int IDProjektila = lista[3].toInt();

        if(nizLaznihNeprijatelja[id])
            nizLaznihNeprijatelja[id]->setBrojZivota(brojZivota);
    }
    else if (niska.contains("gradnja_kule"))
    {
        QStringList koordinate = lista[1].split("-");
        float x = atof(koordinate[0].toStdString().c_str()) - 500;
        float y = atof(koordinate[1].toStdString().c_str()) - 500;
        int redniBroj = atoi(lista[2].toStdString().c_str());
        QStringList koordinateMatrice = lista[3].split("+");
        int i = atoi(koordinateMatrice[0].toStdString().c_str());
        int j = atoi(koordinateMatrice[1].toStdString().c_str());
        int identifikacija = atoi(lista[4].toStdString().c_str());
        int sinhronizovanje = atoi(lista[5].toStdString().c_str());

        matrica[i][j]->setZauzeto(true);

        if (identifikacija == 1) {
            nizLaznihKula[redniBroj] = new LaznaKula1(QPointF(x, y), redniBroj);
            nizLaznihKula[redniBroj]->postaviX(i);
            nizLaznihKula[redniBroj]->postaviY(j);
        }
        scena->addItem(nizLaznihKula[redniBroj]);
        scena->removeItem(domet);

        if (identifikacija == 1 && sinhronizovanje == 0)
            zlato->smanjiZlato(2);
    }
    else if (niska.contains("projektil"))
    {
        QStringList koordinate = lista[1].split("-");
        float x = atof(koordinate[0].toStdString().c_str()) - 500;
        float y = atof(koordinate[1].toStdString().c_str()) - 500;
        int redniBroj = atoi(lista[2].toStdString().c_str());
        int ugao = atoi(lista[3].toStdString().c_str());
        brojacProjektila++;
        nizLaznihProjektila[brojacProjektila] = new LazniProjektil();
        nizLaznihProjektila[brojacProjektila]->setRotation(ugao);
        nizLaznihProjektila[brojacProjektila]->setPos(x, y);
        scena->addItem(nizLaznihProjektila[brojacProjektila]);
    }
    else if (niska.contains("sinhronizacija"))
    {
        QStringList koordinate = lista[1].split("-");
        float x = atof(koordinate[0].toStdString().c_str()) - 500;
        float y = atof(koordinate[1].toStdString().c_str()) - 500;
        int redniBroj = atoi(lista[2].toStdString().c_str());
        int brZivota = atoi(lista[3].toStdString().c_str());
        if(nizLaznihNeprijatelja[redniBroj]) {
            nizLaznihNeprijatelja[redniBroj]->setPos(x, y);
            nizLaznihNeprijatelja[redniBroj]->setBrojZivota(brZivota);
        }
    }

    else if (niska.contains("prodaja_kule"))
    {
        int id = lista[1].toInt();
        int identifikacija = lista[2].toInt();

        int i = nizLaznihKula[id]->vratiX();
        int j = nizLaznihKula[id]->vratiY();
        qDebug() << i << " " << j;
        matrica[i][j]->setZauzeto(false);
        matrica[i][j]->postaviKulu(false);
        scena->removeItem(nizLaznihKula[id]);

        if (identifikacija == 1)
            zlato->povecajZlato(1);
    }
}

void Igra::porukaZaServer() {
    QStringList objekat = server->vratiPoruku().split(" ");
    QStringList koordinate = objekat[0].split("-");

    int identifikacija = objekat[1].toInt();

    brojacKula++;
    Kula1 *KlijentovaKula = new Kula1(brojacKula);
    int xKoordinata = atoi(koordinate[0].toStdString().c_str());
    int yKoordinata = atoi(koordinate[1].toStdString().c_str());
    matrica[xKoordinata][yKoordinata]->postaviKulu(true);
    matrica[xKoordinata][yKoordinata]->setZauzeto(true);
    KlijentovaKula->postaviX(xKoordinata);
    KlijentovaKula->postaviY(yKoordinata);
    listaKula << KlijentovaKula;
    qDebug() << listaKula[listaKula.size() - 1]->vratiX();
    qDebug() << listaKula[listaKula.size() - 1]->vratiY();
    KlijentovaKula->setPos(xKoordinata * SIRINA_POLJA_MREZE, yKoordinata * SIRINA_POLJA_MREZE);
    scena->addItem(KlijentovaKula);

    if (identifikacija == 1)
        zlato->smanjiZlato(2);

    if(xKoordinata + 500 > 0 && yKoordinata + 500 > 0) {
        if(server->imaKorisnika()) {
            server->soket->write("gradnja_kule");
            server->soket->write(" ");
            server->soket->write((std::to_string(xKoordinata * SIRINA_POLJA_MREZE + 500).c_str()));
            server->soket->write("-");
            server->soket->write((std::to_string(yKoordinata * SIRINA_POLJA_MREZE + 500).c_str()));
            server->soket->write(" ");
            server->soket->write((std::to_string(((Kula1*)(KlijentovaKula))->getId()).c_str()));
            server->soket->write(" ");
            server->soket->write((std::to_string(xKoordinata).c_str()));
            server->soket->write("+");
            server->soket->write((std::to_string(yKoordinata).c_str()));
            server->soket->write(" ");
            server->soket->write(std::to_string(KlijentovaKula->identifikacijaKula()).c_str());
            server->soket->write(" ");
            server->soket->write("1");
            server->soket->write(" ");
            server->soket->waitForBytesWritten(1000);
        }

        if(server->imaKorisnika()) {
            server->soket->write("objekat_kraj");
            server->soket->flush();
            server->soket->waitForBytesWritten(1000);
        }
    }
}

void Igra::keyPressEvent(QKeyEvent * event)
{
    if ((rezim == 1 || rezim == 2) && kraj != 1) // ako smo u igri
    {
        if ((event->key() == Qt::Key_Escape) && rezimPauze == 0 && rezimOpcija == 0)
        {
            pauza();
        }
        else if ((event->key() == Qt::Key_Escape) && rezimPauze == 1 && rezimOpcija == 0)
        {
            povratakUIgru();
        }
    }
    else
        return;
}

int Igra::proveraPuta(int x, int y) {
    int provera = 0;
    if(x - 1 >= 0) {
        if(matrica[x - 1][y]->getZauzeto() == true)
            provera += 1;
    }
    if(y + 1 < BR_POLJA_PO_VISINI) {
        if(matrica[x][y + 1]->getZauzeto() == true)
            provera += 2;
    }
    if(x + 1 < BR_POLJA_PO_SIRINI) {
        if(matrica[x + 1][y]->getZauzeto() == true)
            provera += 4;
    }
    if(y - 1 >= 0) {
        if(matrica[x][y - 1]->getZauzeto() == true)
            provera += 8;
    }
    if(provera == 4 || provera == 5)
        return 1;
    else if(provera == 12)
        return 2;
    else if(provera == 10)
        return 3;
    else if(provera == 6)
        return 4;
    else if(provera == 2 || provera == 3)
        return 5;
    else
        return 6;
}

void Igra::stvoriPut(){
    SlucajnaPutanja *putanja = new SlucajnaPutanja(BR_POLJA_PO_SIRINI, BR_POLJA_PO_VISINI, 0, 4, BR_POLJA_PO_SIRINI - 1, 4, 50);

    putanjaKretanja << QPointF(putanja->niz[0].x - 100 + SIRINA_POLJA_MREZE / 2,
            putanja->niz[0].y * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2);

    for(uint i = 0; i < putanja->niz.size(); i++) {
        matrica[putanja->niz[i].x][putanja->niz[i].y]->setZauzeto(true);
        putanjaKretanja << QPointF(putanja->niz[i].x * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2,
                                   putanja->niz[i].y * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2);
        if(server->imaKorisnika()) {
            server->soket->write((std::to_string(putanja->niz[i].x)).c_str());
            server->soket->write("-");
            server->soket->write((std::to_string(putanja->niz[i].y)).c_str());
            server->soket->write(" ");
            server->soket->waitForBytesWritten(1000);
        }
    }
    if(server->imaKorisnika()) {
        server->soket->write("put_kraj");
        server->soket->flush();
        server->soket->waitForBytesWritten(1000);
    }

    for(uint i = 0; i < putanja->niz.size() - 1; i++) {
        int pravac = proveraPuta(putanja->niz[i].x, putanja->niz[i].y);
        matrica[putanja->niz[i].x][putanja->niz[i].y]->dodatak->setPixmap(QPixmap(QString(":/put/slike/put/s%1.png").arg(pravac)));
        scena->addItem(matrica[putanja->niz[i].x][putanja->niz[i].y]->dodatak);
    }

    QPointF poz = QPointF(putanja->niz[putanja->niz.size() - 1].x * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2,
            putanja->niz[putanja->niz.size() - 1].y * SIRINA_POLJA_MREZE + SIRINA_POLJA_MREZE / 2);
    Baza *baza = new Baza(poz);

    baza->setPos(baza->vratiPoziciju().x() - SIRINA_POLJA_MREZE / 2, baza->vratiPoziciju().y() - SIRINA_POLJA_MREZE / 2);
    scena->addItem(baza);
}

void Igra::stvoriBarbarian_Kraljeve(int brojBarbarian_Kraljeva, int sekundi){
    brojKreiranihBarbarian_Kraljeva = 0;
    maksimalniBrojBarbarian_Kraljeva = brojBarbarian_Kraljeva;
    connect(tajmerKreiranjaBarbarian_Kraljeva,SIGNAL(timeout()),this,SLOT(stvoriJednogBarbarian_Kralja()));
    tajmerKreiranjaBarbarian_Kraljeva->start(1000*sekundi);
}


void Igra::stvoriJednogBarbarian_Kralja(){
    nizNeprijatelja[brojacNeprijatelja] = new Barbarian_King(putanjaKretanja, 10, brojacNeprijatelja, 0);
    nizNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
    scena->addItem(nizNeprijatelja[brojacNeprijatelja]);
    brojKreiranihBarbarian_Kraljeva += 1;

    if(server->imaKorisnika()) {
        server->soket->write("napravi_Barbarian_Kinga");
        server->soket->write(" ");
        server->soket->write("objekat_kraj");
        server->soket->flush();
        server->soket->waitForBytesWritten(1000);
    }

    if (brojKreiranihBarbarian_Kraljeva >= maksimalniBrojBarbarian_Kraljeva){
        tajmerKreiranjaBarbarian_Kraljeva->disconnect();
    }
}


void Igra::stvoriBarbare(int brojBarbara, int sekundi){
    brojKreiranihBarbara = 0;
    maksimalniBrojBarbara = brojBarbara;
    connect(tajmerKreiranjaBarbara,SIGNAL(timeout()),this,SLOT(stvoriJednogBarbara()));
    tajmerKreiranjaBarbara->start(1000*sekundi);
}

void Igra::stvoriJednogBarbara(){
    nizNeprijatelja[brojacNeprijatelja] = new Barbar(putanjaKretanja, 5, brojacNeprijatelja, 0);
    nizNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
    scena->addItem(nizNeprijatelja[brojacNeprijatelja++]);
    brojKreiranihBarbara += 1;

    if(server->imaKorisnika()) {
        server->soket->write("napravi_Barbara");
        server->soket->write(" ");
        server->soket->write("objekat_kraj");
        server->soket->flush();
        server->soket->waitForBytesWritten(1000);
    }

    if (brojKreiranihBarbara >= maksimalniBrojBarbara){
        tajmerKreiranjaBarbara->disconnect();
    }
}

void Igra::stvoriOrke(int brojOrka, int sekundi){
    brojKreiranihOrka = 0;
    maksimalniBrojOrka = brojOrka;
    connect(tajmerKreiranjaOrka,SIGNAL(timeout()),this,SLOT(stvoriJednogOrka()));
    tajmerKreiranjaOrka->start(1000*sekundi);
}

void Igra::stvoriJednogOrka(){
    nizNeprijatelja[brojacNeprijatelja] = new Ork(putanjaKretanja, 7, brojacNeprijatelja, 0);
    nizNeprijatelja[brojacNeprijatelja]->setPos(putanjaKretanja[0].x()-150, putanjaKretanja[0].y()-POLOVINA_SIRINE);
    scena->addItem(nizNeprijatelja[brojacNeprijatelja]);
    brojKreiranihOrka += 1;

    if(server->imaKorisnika()) {
        server->soket->write("napravi_Orka");
        server->soket->write(" ");
        server->soket->write("objekat_kraj");
        server->soket->flush();
        server->soket->waitForBytesWritten(1000);
    }

    if (brojKreiranihOrka >= maksimalniBrojOrka){
        tajmerKreiranjaOrka->disconnect();
    }
}

void Igra::pokreniNivo(){

    if(tajmerZaNivo){

        delete tajmerZaNivo;
        tajmerZaNivo = NULL;
    }
    tajmerZaNivo = new QTimer(this);
    connect(tajmerZaNivo,SIGNAL(timeout()),this,SLOT(pokreniNivo()));

    tajmerKreiranjaBarbara = new QTimer(this);
    brojKreiranihBarbara = 0;
    maksimalniBrojBarbara = 0;

    tajmerKreiranjaOrka = new QTimer(this);
    brojKreiranihOrka = 0;
    maksimalniBrojOrka = 0;

    tajmerKreiranjaBarbarian_Kraljeva = new QTimer(this);
    brojKreiranihBarbarian_Kraljeva = 0;
    maksimalniBrojBarbarian_Kraljeva = 0;

    if(nivo==2)
    {
        brojBarbaraUNivou = 0;
        brojOrkovaUNivou = 10;
        brojBarbarianKingovaUNivou = 0;

        stvoriOrke(brojOrkovaUNivou,2);
    }
    else if(nivo==3)
    {
        brojBarbaraUNivou = 0;
        brojOrkovaUNivou = 0;
        brojBarbarianKingovaUNivou = 10;

        stvoriBarbarian_Kraljeve(brojBarbarianKingovaUNivou, 2);
    }

    brojNeprijateljaUNivou = brojOrkovaUNivou + brojBarbarianKingovaUNivou + brojBarbaraUNivou;
}

void Igra::pokreniIgru(){

    brojacKula = 0;
    brojacNeprijatelja = 0;

    server = new Server();

    rezim = 1;
    kraj = 0;

    plejlista->setCurrentIndex(1);
    plejer->setPosition(0);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    // uklanjanje dugmica iz prethodne scene
    btnZapocni->close();
    btnPrikljuciSe->close();
    btnOpcije->close();
    btnPravila->close();
    btnIzlaz->close();

    kursor = 0;
    gradnja = 0;
    setMouseTracking(true);

    matrica = new Polje**[BR_POLJA_PO_SIRINI];

    for(int i = 0; i < BR_POLJA_PO_SIRINI; i++) {
        matrica[i] = new Polje*[BR_POLJA_PO_VISINI];
        for(int j = 0; j < BR_POLJA_PO_VISINI; j++) {
            matrica[i][j] = new Polje(i * SIRINA_POLJA_MREZE, j * SIRINA_POLJA_MREZE);
            scena->addItem(matrica[i][j]);
            matrica[i][j]->setZauzeto(false);
        }
    }

    tajmerZaNivo = new QTimer(this);
    connect(tajmerZaNivo,SIGNAL(timeout()),this,SLOT(pokreniNivo()));

    tajmerKreiranjaBarbarian_Kraljeva = new QTimer(this);
    brojKreiranihBarbarian_Kraljeva = 0;
    maksimalniBrojBarbarian_Kraljeva = 0;

    tajmerKreiranjaBarbara = new QTimer(this);
    brojKreiranihBarbara = 0;
    maksimalniBrojBarbara = 0;

    tajmerKreiranjaOrka = new QTimer(this);
    brojKreiranihOrka = 0;
    maksimalniBrojOrka = 0;

    brojBarbaraUNivou = 10;
    brojBarbarianKingovaUNivou = 0;
    brojOrkovaUNivou = 0;

    brojNeprijateljaUNivou = brojOrkovaUNivou + brojBarbarianKingovaUNivou + brojBarbaraUNivou;

    //stvoriBarbarian_Kraljeve(brojBarbarianKingovaUNivou, 25);
    stvoriBarbare(brojBarbaraUNivou,2);
    //stvoriOrke(brojOrkovaUNivou,10);

    stvoriPut();

    QGraphicsPixmapItem* pozadinaMenija = new QGraphicsPixmapItem();
    QPixmap pozadina = QPixmap(":/1/pozadinaDesno.png");
    pozadinaMenija->setPixmap(pozadina);
    pozadinaMenija->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,0);

    scene()->addItem(pozadinaMenija);

    poeni = new Poeni(0,QString("Poeni"));
    scene()->addItem(poeni);
    poeni->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 10);

    zlato = new Poeni(0,QString("Zlato"));
    scene()->addItem(zlato);
    zlato->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 50);

    zivotBaze = new Poeni(0,QString("ZivotBaze"));
    scene()->addItem(zivotBaze);
    zivotBaze->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 90);

    poruka = new Poeni(0,QString("Poruka"));
    scene()->addItem(poruka);
    poruka->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 130);

    porukaNivo = new Poeni(0,QString("Nivo"));
    scene()->addItem(porukaNivo);
    porukaNivo->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 170);

    PravljenjeKule1 * t1 = new PravljenjeKule1();
    PravljenjeKuleLovac * t2 = new PravljenjeKuleLovac();
    PravljenjeKuleStrelac * t3 = new PravljenjeKuleStrelac();
    PravljenjeKuleTop * t4 = new PravljenjeKuleTop();
    t1->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y()+300);
    t2->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y()+400);
    t3->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 80,y()+300);
    t4->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 80,y()+400);

    scena->addItem(t1);
    scena->addItem(t2);
    scena->addItem(t3);
    scena->addItem(t4);

    connect(server, SIGNAL(ucitanaPoruka()), this, SLOT(porukaZaServer()));
}

void Igra::prikljuciSeIgri() {
    rezim = 2;
    kraj = 0;

    // muzika
    plejlista->setCurrentIndex(1);
    plejer->setPosition(0);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    // uklanjanje dugmica iz prethodne scene
    btnZapocni->close();
    btnPrikljuciSe->close();
    btnOpcije->close();
    btnPravila->close();
    btnIzlaz->close();

    kursor = 0;
    gradnja = 0;
    setMouseTracking(true);

    matrica = new Polje**[BR_POLJA_PO_SIRINI];

    for(int i = 0; i < BR_POLJA_PO_SIRINI; i++) {
        matrica[i] = new Polje*[BR_POLJA_PO_VISINI];
        for(int j = 0; j < BR_POLJA_PO_VISINI; j++) {
            matrica[i][j] = new Polje(i * SIRINA_POLJA_MREZE, j * SIRINA_POLJA_MREZE);
            scena->addItem(matrica[i][j]);
            matrica[i][j]->setZauzeto(false);
        }
    }

    tajmerKreiranjaBarbarian_Kraljeva = new QTimer(this);

    tajmerKreiranjaBarbara = new QTimer(this);

    QGraphicsPixmapItem* pozadinaMenija = new QGraphicsPixmapItem();
    QPixmap pozadina = QPixmap(":/1/pozadinaDesno.png");
    pozadinaMenija->setPixmap(pozadina);
    pozadinaMenija->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,0);

    scene()->addItem(pozadinaMenija);

    poeni = new Poeni(0,QString("Poeni"));
    scene()->addItem(poeni);
    poeni->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 10);

    zlato = new Poeni(0,QString("Zlato"));
    scene()->addItem(zlato);
    zlato->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 50);

    zivotBaze = new Poeni(0,QString("ZivotBaze"));
    scene()->addItem(zivotBaze);
    zivotBaze->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 90);

    poruka = new Poeni(0,QString("Poruka"));
    scene()->addItem(poruka);
    poruka->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y() + 130);

    PravljenjeKule1 * t1 = new PravljenjeKule1();
    PravljenjeKuleLovac * t2 = new PravljenjeKuleLovac();
    PravljenjeKuleStrelac * t3 = new PravljenjeKuleStrelac();
    PravljenjeKuleTop * t4 = new PravljenjeKuleTop();
    t1->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y()+300);
    t2->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE,y()+400);
    t3->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 80,y()+300);
    t4->setPos(BR_POLJA_PO_SIRINI*SIRINA_POLJA_MREZE + 80,y()+400);

    scena->addItem(t1);
    scena->addItem(t2);
    scena->addItem(t3);
    scena->addItem(t4);

    klijent = new Klijent();
    klijent->Test();
    connect(klijent, SIGNAL(ucitanPut()), this, SLOT(putZaKlijenta()));
    connect(klijent, SIGNAL(ucitanObjekat()), this, SLOT(objekatZaKlijenta()));
}

void Igra::opcije()
{
    rezimOpcija = 1;
    QTimer::singleShot(100, [this] () {

        if (rezimPauze == 1)
        {
            pravougaonik2 = new QGraphicsPixmapItem();
            QPixmap pr(":/1/pravougaonik2.png");
            pravougaonik2->setPixmap(pr);
            pravougaonik2->setScale(10);
            scena->addItem(pravougaonik2);
        }
        else
            scena->clear();

        tekst1 = new QGraphicsTextItem("Zvuk: ");
        tekst1->moveBy(3 * SIRINA_PROZORA / 7 , VISINA_PROZORA / 3 - RAZMAK);
        tekst1->setDefaultTextColor("#663300");
        tekst1->setFont(QFont("times",20));
        scena->addItem(tekst1);

        // namestanje slajdera za kontrolu zvuka
        jacinaZvuka = new QSlider(Qt::Horizontal);
        jacinaZvuka->setRange(0, 100);
        jacinaZvuka->setSingleStep(1);
        jacinaZvuka->setFixedSize(150, 24);
        jacinaZvuka->setValue(plejer->volume());

        jacinaZvuka->move(SIRINA_PROZORA / 2, VISINA_PROZORA / 3);
        scena->addWidget(jacinaZvuka);
        connect(jacinaZvuka, SIGNAL(valueChanged(int)), this, SLOT(podesiJacinu()));

        QBrush* brush = new QBrush();
        QPalette* palette = new QPalette();

        tekst2 = new QGraphicsTextItem("Fullscreen: ");
        tekst2->moveBy(3 * SIRINA_PROZORA / 7 , VISINA_PROZORA / 3);
        tekst2->setDefaultTextColor("#663300");
        tekst2->setFont(QFont("times",20));
        scena->addItem(tekst2);

        // radio button-i za biranje fullscreen-a
        fullscreen = new QButtonGroup();
        rb1 = new QRadioButton("Da");
        rb2 = new QRadioButton("Ne");
        fullscreen->addButton(rb1);
        fullscreen->addButton(rb2);
        fullscreen->setExclusive(true);

        if (QGraphicsView::isFullScreen() == true)
            rb1->setChecked(true);
        else
            rb2->setChecked(true);

        rb1->move(SIRINA_PROZORA / 2, VISINA_PROZORA / 3 + RAZMAK);
        rb2->move(SIRINA_PROZORA / 2 + 2 * RAZMAK, VISINA_PROZORA / 3 + RAZMAK);

        connect(rb1,SIGNAL(toggled(bool)),this,SLOT(ceoEkran()));
        connect(rb2,SIGNAL(toggled(bool)),this,SLOT(prozor()));

        // dugme za povratak na meni
        QPixmap dugme9(":/1/VratiSe.png");
        btnPovratak = new Dugme(dugme9, (SIRINA_PROZORA - dugme9.width()) / 2 + 100, 3 * VISINA_PROZORA / 4);

        connect(btnPovratak, SIGNAL(clicked(bool)), this, SLOT(vratiSe()));

        scena->addWidget(btnPovratak);
        scena->addWidget(rb1);
        scena->addWidget(rb2);
    });
}

void Igra::pokreniGlavniMeni()
{
    // muzika
    plejlista->setCurrentIndex(0);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    // pozadina
    setStyleSheet("background-color: #DDA85A");

    // naslov
    QPixmap logo = QPixmap(":/1/logo.png");
    QGraphicsPixmapItem * naslov = new QGraphicsPixmapItem();
    naslov->setPixmap(logo);
    scena->addItem(naslov);
    naslov->moveBy((SIRINA_PROZORA - naslov->pixmap().width()) / 2 + 100, (SIRINA_PROZORA - naslov->pixmap().width()) / 2 - 3 * RAZMAK);

    // podesavanje slika dugmica
    QPixmap dugme0(":/1/ZapocniIgru.png");
    QPixmap dugme1(":/1/PrikljuciSe.png");
    QPixmap dugme2(":/1/Opcije.png");
    QPixmap dugme3(":/1/PravilaIgre.png");
    QPixmap dugme4(":/1/Izlaz.png");

    // dugme za zapocinjanje igre
    btnZapocni = new Dugme(dugme0, (SIRINA_PROZORA - dugme0.width()) / 2 + 100, VISINA_PROZORA / 2 - 5 * VISINA_DUGMETA / 2 + RAZMAK);

    // dugme za prikljucivanje igri
    btnPrikljuciSe = new Dugme(dugme1, (SIRINA_PROZORA - dugme1.width()) / 2 + 100, VISINA_PROZORA / 2 - 3 * VISINA_DUGMETA / 2 + 2 * RAZMAK);

    // dugme za opcije
    btnOpcije = new Dugme(dugme2, (SIRINA_PROZORA - dugme2.width()) / 2 + 100, VISINA_PROZORA / 2 - VISINA_DUGMETA / 2 + 3 * RAZMAK);

    // dugme za pravila
    btnPravila = new Dugme(dugme3, (SIRINA_PROZORA - dugme3.width()) / 2 + 100, VISINA_PROZORA / 2 + VISINA_DUGMETA / 2 + 4 * RAZMAK);

    // dugme za izlaz
    btnIzlaz = new Dugme(dugme4, (SIRINA_PROZORA - dugme4.width()) / 2 + 100, VISINA_PROZORA / 2 + 3 * VISINA_DUGMETA / 2 + 5 * RAZMAK);

    // konekcije
    connect(btnZapocni, SIGNAL(clicked(bool)), this, SLOT(pokreniIgru()));
    connect(btnPrikljuciSe, SIGNAL(clicked(bool)), this, SLOT(prikljuciSeIgri()));
    connect(btnIzlaz, SIGNAL(clicked(bool)), this, SLOT(izlaz()));
    connect(btnOpcije, SIGNAL(clicked(bool)), this, SLOT(opcije()));

    // dodavanje na scenu
    scena->addWidget(btnZapocni);
    scena->addWidget(btnPrikljuciSe);
    scena->addWidget(btnOpcije);
    scena->addWidget(btnPravila);
    scena->addWidget(btnIzlaz);
}

void Igra::pauza()
{
    rezimPauze = 1;

    poruka->izbrisiPoruku();
    brisanjeProdaje();

    if(tajmerKreiranjaBarbarian_Kraljeva){
        delete tajmerKreiranjaBarbarian_Kraljeva;
        tajmerKreiranjaBarbarian_Kraljeva = NULL;
    }

    if(tajmerKreiranjaBarbara){
        delete tajmerKreiranjaBarbara;
         tajmerKreiranjaBarbara = NULL;
    }
    if(tajmerKreiranjaOrka){
        delete tajmerKreiranjaOrka;
        tajmerKreiranjaOrka = NULL;
    }
    if(tajmerZaNivo){
        protekloMilisekundi = t.elapsed();
        milisekundeZaNivo =  tajmerZaNivo->interval();

        qDebug() << tajmerZaNivo->isActive() << milisekundeZaNivo << "-" << protekloMilisekundi << "=" << milisekundeZaNivo-protekloMilisekundi ;

        delete tajmerZaNivo;
        tajmerZaNivo = NULL;
    }

    // muzika
    pozicijaPesme = plejer->position();
    plejlista->setCurrentIndex(2);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    // pravougaonik
    pravougaonik = new QGraphicsPixmapItem();
    QPixmap pr(":/1/pozadinaUPauzi.png");
    pravougaonik->setPixmap(pr);
    pravougaonik->setOpacity(0.65);
    pravougaonik->setScale(10);

    // pauzaLogo
    pauzaLogo = new QGraphicsPixmapItem();
    QPixmap pl(":/1/Pauza.png");
    pauzaLogo->setPixmap(pl);
    pauzaLogo->setPos((SIRINA_PROZORA - pl.width())/2 + 100, (SIRINA_PROZORA - pauzaLogo->pixmap().width()) / 2 - 8 * RAZMAK);

    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    // dugme za povratak u igru
    QPixmap dugme5(":/1/PovratakUIgru.png");
    btnIgra = new Dugme(dugme5, (SIRINA_PROZORA - dugme5.width()) / 2 + 100, VISINA_PROZORA / 2);

    // dugme za povratak na glavni meni
    QPixmap dugme6(":/1/PovratakNaMeni.png");
    btnMeni = new Dugme(dugme6, (SIRINA_PROZORA - dugme6.width()) / 2 + 100, VISINA_PROZORA / 2 + 2 * VISINA_DUGMETA + 2 * RAZMAK);

    // dugme za opcije
    QPixmap dugme7(":/1/Opcije.png");
    btnOpcijeP = new Dugme(dugme7, (SIRINA_PROZORA - dugme7.width()) / 2 + 100, VISINA_PROZORA / 2 + VISINA_DUGMETA + RAZMAK);

    // konekcije
    connect(btnIgra, SIGNAL(clicked(bool)), this, SLOT(povratakUIgru()));
    connect(btnMeni, SIGNAL(clicked(bool)), this, SLOT(povratakNaMeni()));
    connect(btnOpcijeP, SIGNAL(clicked(bool)), this, SLOT(opcije()));

    // dodavanje na scenu
    scena->addItem(pravougaonik);
    scena->addItem(pauzaLogo);
    scena->addWidget(btnIgra);
    scena->addWidget(btnMeni);
    scena->addWidget(btnOpcijeP);
}

void Igra::izlaz()
{
    this->close();
}

void Igra::povratakUIgru()
{
    // muzika
    plejlista->setCurrentIndex(1);
    plejer->setPosition(pozicijaPesme);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    scena->removeItem(pravougaonik);
    scena->removeItem(pauzaLogo);
    btnIgra->close();
    btnMeni->close();
    btnOpcijeP->close();

    tajmerZaNivo = new QTimer(this);
    connect(tajmerZaNivo,SIGNAL(timeout()),this,SLOT(pokreniNivo()));

    if(milisekundeZaNivo > 0){
        tajmerZaNivo->start(milisekundeZaNivo-protekloMilisekundi);
        t.restart();
        milisekundeZaNivo = 0;
    }

    if(brojKreiranihBarbarian_Kraljeva < maksimalniBrojBarbarian_Kraljeva){
        tajmerKreiranjaBarbarian_Kraljeva = new QTimer();
        connect(tajmerKreiranjaBarbarian_Kraljeva,SIGNAL(timeout()),this,SLOT(stvoriJednogBarbarian_Kralja()));
        tajmerKreiranjaBarbarian_Kraljeva->start(2000);
    }
    if( brojKreiranihBarbara < maksimalniBrojBarbara){
        tajmerKreiranjaBarbara = new QTimer();
        connect(tajmerKreiranjaBarbara,SIGNAL(timeout()),this,SLOT(stvoriJednogBarbara()));
        tajmerKreiranjaBarbara->start(2000);
    }

    if(brojKreiranihOrka < maksimalniBrojOrka){
        tajmerKreiranjaOrka = new QTimer();
        connect(tajmerKreiranjaOrka,SIGNAL(timeout()),this,SLOT(stvoriJednogOrka()));
        tajmerKreiranjaOrka->start(2000);
    }

    rezimPauze = 0;
}

void Igra::povratakNaMeni()
{
    // muzika
    plejlista->setCurrentIndex(0);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    for(int i = 0; i < BR_POLJA_PO_SIRINI; i++)
        delete matrica[i];

    delete matrica;

    putanjaKretanja.clear();

    QTimer::singleShot(100, [this] () {
        // uklanjanje svih elemenata iz rezima igre
        scena->clear();
        if(rezim == 1)
            delete server;
        else if(rezim == 2)
            delete klijent;

        // ulazenje u glavni meni
        rezim = 0;
        rezimPauze = 0;
        pokreniGlavniMeni();
    });
}

void Igra::krajIgre()
{
    rezimPauze = 1;
    kraj = 1;
    tajmerKreiranjaBarbarian_Kraljeva->disconnect();
    tajmerKreiranjaBarbara->disconnect();

    // muzika
    pozicijaPesme = plejer->position();
    plejlista->setCurrentIndex(2);
    plejlista->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    plejer->play();

    // pravougaonik
    pravougaonik = new QGraphicsPixmapItem();
    QPixmap pr(":/1/pozadinaUPauzi.png");
    pravougaonik->setPixmap(pr);
    pravougaonik->setOpacity(0.65);
    pravougaonik->setScale(10);

    // logo za kraj igre
    logoKraj = new QGraphicsPixmapItem();
    QPixmap ki(":/1/KrajIgre.png");
    logoKraj->setPixmap(ki);
    logoKraj->setPos((SIRINA_PROZORA - ki.width())/2 + 100, (SIRINA_PROZORA - logoKraj->pixmap().width()) / 2 - 6 * RAZMAK);

    // poruka o osvojenim poenima
    QGraphicsTextItem * tekst2 = new QGraphicsTextItem("Osvojili ste " + QString::number(poeni->getPoeni()) + " poena!");
    tekst2->setTextWidth(800);
    tekst2->moveBy((SIRINA_PROZORA + 100) / 2, VISINA_PROZORA / 2);
    tekst2->setDefaultTextColor(Qt::black);
    tekst2->setFont(QFont("times",36));

    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();

    // dugme za povratak na glavni meni
    QPixmap dugme8(":/1/PovratakNaMeni.png");
    btnMeni2 = new Dugme(dugme8, (SIRINA_PROZORA - dugme8.width()) / 2 + 100, VISINA_PROZORA / 2 + 2 * VISINA_DUGMETA + 2 * RAZMAK);

    // konekcija
    connect(btnMeni2, SIGNAL(clicked(bool)), this, SLOT(povratakNaMeni()));

    // dodavanje na scenu
    scena->addItem(pravougaonik);
    scena->addItem(logoKraj);
    scena->addWidget(btnMeni2);
    scena->addItem(tekst2);
}

// MZ
void Igra::ceoEkran() {
    if (QGraphicsView::isFullScreen() == false)
    {
        QGraphicsView::scale(skaliranjePoX, skaliranjePoY);
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void Igra::prozor() {
    if (QGraphicsView::isFullScreen() == true)
    {
        QGraphicsView::scale(1.0/skaliranjePoX, 1.0/skaliranjePoY);
        this->showNormal();
    }
}
