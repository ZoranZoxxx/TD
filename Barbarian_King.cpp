#include "Barbarian_King.h"
#include "Neprijatelj.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Igra.h"
#include <QDebug>
#include <QString>
#include <QTime>
#include "Umiranje.h"

extern Igra* igra;

Barbarian_King::Barbarian_King(QList<QPointF> nizTacaka, int brZivota, int id, QGraphicsItem *roditelj)
    : Neprijatelj(nizTacaka, brZivota, id){

    this->id = id;

    tajmerSinhronizacije = new QTimer(this);
    connect(tajmerSinhronizacije,SIGNAL(timeout()),this,SLOT(sinhronizacija()));
    tajmerSinhronizacije->start(500);

    SIRINA_POLJA_MREZE = 96;
    POLOVINA_SIRINE_POLJA_MREZE = SIRINA_POLJA_MREZE/2;
    POLOVINA_SIRINE_SLICICE = 48;
    BROJ_SMEROVA = 8;

    redniBrojKretanje = 0;

    trenutniBrojZivota = getBrojZivota();
    pocetniBrojZivota = trenutniBrojZivota;

    zvukSmrti = new QMediaPlayer();
    zvukSmrti->setMedia(QUrl("qrc:/1/smrt.WAV"));

    tipNeprijatelja = 0;

    BROJ_SIMULACIJA_KRETANJE = 8;
    for(int i = 0; i < BROJ_SMEROVA; i++) {
        for(int j = 0; j < BROJ_SIMULACIJA_KRETANJE; j++){
            QString smer;
            switch( i )
            {
            case 0:
                smer = "e";
                break ;
            case 1:
                smer = "ne";
                break ;
            case 2:
                smer = "n";
                break ;
            case 3:
                smer = "nw";
                break ;
            case 4:
                smer = "w";
                break ;
            case 5:
                smer = "sw";
                break ;
            case 6:
                smer = "s";
                break ;
            case 7:
                smer = "se";
                break ;
            }
            QString putanja = QString(":/slike/slike/barbarian_king/walking/walking %00000%1.png").arg(smer).arg(j);
            matricaKretanje[i][j] = putanja;
        }
    }

    tacke = nizTacaka;
    indeks = 0;
    destinacija.setX(tacke[0].x() - POLOVINA_SIRINE_POLJA_MREZE);
    destinacija.setY(tacke[0].y() - POLOVINA_SIRINE_POLJA_MREZE);

    heltBar1 = new QGraphicsRectItem(this);//m
    heltBar1->setRect(x()+10,y(),30,5);//m
    heltBar1->setBrush(Qt::black);//m
    igra->scene()->addItem(heltBar1);//m
    heltBar2 = new QGraphicsRectItem(this);//m
    heltBar2->setRect(x()+10,y(),30,5);//m
    heltBar2->setBrush(Qt::green);//m
    igra->scene()->addItem(heltBar2);//m

    QTimer * tajmer = new QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(pomeriNapred()));
    tajmer->start(100);
}

void Barbarian_King::pomeriNapred(){
    if (igra->rezimPauze != 1) {
        QLineF ln(pos(),destinacija);

        //ako nema vise zivota
        if(this->getBrojZivota() <=0)
        {
            if (this->getBrojZivota() == 0)
            {
                zvukSmrti->setVolume(igra->plejer->volume());
                zvukSmrti->play();
            }

            igra->scena->removeItem(this);
            igra->scena->removeItem(heltBar1);
            igra->scena->removeItem(heltBar2);
            delete heltBar1;
            delete heltBar2;
            QPointF pozicija = pos();

            int ugao = (int)(ln.angle()) / 45;
            Umiranje* smrt = new Umiranje(tipNeprijatelja,ugao,0);
            smrt->setPos(pozicija);
            igra->scene()->addItem(smrt);

            delete this;
            igra->poeni->povecajPoene();
            igra->zlato->povecajZlato(1);
            igra->brojNeprijateljaUNivou--;
            qDebug() << igra->brojNeprijateljaUNivou;
            if(igra->brojNeprijateljaUNivou <= 0 && igra->nivo < igra->brojNivoa){//ako je unisten poslednji neprijatelj
                igra->poruka->novaPoruka(QString("Presli ste nivo!"));
                igra->nivo++;
                qDebug()<< igra->nivo;
                igra->porukaNivo->povecajNivo();
                igra->tajmerZaNivo->start(7000);
                igra->t.start();
            }
            else if(igra->brojNeprijateljaUNivou <= 0)
            {
                igra->krajIgre();
            }
            return;
        }

        if(this->getBrojZivota() < trenutniBrojZivota)
        {
            trenutniBrojZivota = this->getBrojZivota();
        }

        if (ln.length() < 8){
            indeks++;
            if (indeks >= tacke.size()){
                igra->zivotBaze->smanjiZivotBaze();
                if(igra->zivotBaze->getZivotBaze() == 0)
                {
                    igra->krajIgre();
                }
                delete heltBar1;
                delete heltBar2;
                delete this;
                return;
            }

            destinacija.setX(tacke[indeks].x() - POLOVINA_SIRINE_POLJA_MREZE);
            destinacija.setY(tacke[indeks].y() - POLOVINA_SIRINE_POLJA_MREZE);
        }

        bool redniBrojPovecan = false;

        if(redniBrojKretanje < BROJ_SIMULACIJA_KRETANJE) {
            setPixmap(QPixmap(matricaKretanje[(int)(ln.angle()) / 45][redniBrojKretanje]));
            redniBrojKretanje++;
            redniBrojPovecan = true;
        }
        else {
            redniBrojKretanje = 0;
            setPixmap(QPixmap(matricaKretanje[(int)(ln.angle()) / 45][redniBrojKretanje]));
        }

        setTransformOriginPoint(POLOVINA_SIRINE_SLICICE, POLOVINA_SIRINE_SLICICE);
        setRotation(-1 * ((int)(ln.angle()) % 45));

        int POMERAJ = 5;

        double dy = POMERAJ * qSin(qDegreesToRadians(-1 * ln.angle()));
        double dx = POMERAJ * qCos(qDegreesToRadians(-1 * ln.angle()));

        setPos(x()+dx, y()+dy);
        heltBar1->setRect(x()+20,y(),30,5);//m
        heltBar1->setBrush(Qt::black);//m
        heltBar2->setRect(x()+20,y(),30 * trenutniBrojZivota/pocetniBrojZivota,5);//m
        if((float)trenutniBrojZivota/pocetniBrojZivota > 0.5)//m
            heltBar2->setBrush(Qt::green);//m
        else if((float)trenutniBrojZivota/pocetniBrojZivota > 0.25)//m
            heltBar2->setBrush(Qt::yellow);//m
        else
            heltBar2->setBrush(Qt::red);//m
    }
}

void Barbarian_King::sinhronizacija() {
    if(igra->server->imaKorisnika()) {
        igra->server->soket->write("sinhronizacija");
        igra->server->soket->write(" ");
        igra->server->soket->write((std::to_string(x() + 500).c_str()));
        igra->server->soket->write("-");
        igra->server->soket->write((std::to_string(y() + 500).c_str()));
        igra->server->soket->write(" ");
        igra->server->soket->write((std::to_string(id).c_str()));
        igra->server->soket->write(" ");
        igra->server->soket->write((std::to_string(getBrojZivota()).c_str()));
        igra->server->soket->write(" ");
        igra->server->soket->waitForBytesWritten(1000);
    }

    if(igra->server->imaKorisnika()) {
        igra->server->soket->write("objekat_kraj");
        igra->server->soket->flush();
        igra->server->soket->waitForBytesWritten(1000);
    }
}
