#include "KulaTop.h"
#include <QTimer>
#include "Projektil.h"
#include "Igra.h"
#include "Neprijatelj.h"
#include <math.h>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>

extern Igra * igra;

KulaTop::KulaTop(int id, QGraphicsItem *roditelj)
    : Kula(id) /* MZ*/{
    this->id = id;

    // zvuk
    zvukStrele = new QMediaPlayer();
    zvukStrele->setMedia(QUrl("qrc:/1/EXPLO1.WAV"));

    for(int i = 0; i < BROJ_SMEROVA; i++) {
        for(int j = 0; j < BR_SIMULACIJA_GADJANJA; j++){
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
            QString putanja = QString(":/slike/slike/top/schuss %00000%1.png").arg(smer).arg(j);
                        matricaSlika[i][j] = putanja;
        }
    }

    setPixmap(QPixmap(matricaSlika[0][0]));

    PRECNIK_KRUGA_DOMETA = 270;
    POLOVINA_SIRINE_KULE = 48;


    int a = PRECNIK_KRUGA_DOMETA;
    int b = PRECNIK_KRUGA_DOMETA;
    double polovina_a = a/2;
    double polovina_b = b/2;

    domet = new QGraphicsEllipseItem(-1*polovina_a + POLOVINA_SIRINE_KULE, -1*polovina_b + POLOVINA_SIRINE_KULE, a, b, this);
    domet->setOpacity(0);


    meta = QPointF(0,0);
    metaPronadjena = false;

    connect(tajmer,SIGNAL(timeout()),this,SLOT(pronadjiMetu()));
    tajmer->start(300);
}

void KulaTop::pucaj(){

    if (igra->rezimPauze != 1){
        QLineF ln(QPointF(x()+POLOVINA_SIRINE_KULE,y()+POLOVINA_SIRINE_KULE),meta);

        setPixmap(QPixmap(matricaSlika[(int)(ln.angle()) / 45][redniBroj]));
        setTransformOriginPoint(POLOVINA_SIRINE_KULE, POLOVINA_SIRINE_KULE);
        setRotation(-1 * ((int)(ln.angle()) % 45));

        if(redniBroj == 3) {
            (igra->brojacProjektila)++;
            //qDebug() << "brojac projektila: " << igra->brojacProjektila;
            Projektil * projektil = new Projektil(igra->brojacProjektila, PRECNIK_KRUGA_DOMETA/2, 1);

            zvukStrele->setVolume(igra->plejer->volume());
            zvukStrele->play();


            projektil->setPos(x()+POLOVINA_SIRINE_KULE,y()+POLOVINA_SIRINE_KULE);

            int ugao = -1 * ln.angle();

            projektil->setRotation(ugao);
            igra->scena->addItem(projektil);

            if(igra->server->imaKorisnika()) {
                igra->server->soket->write("projektil");
                igra->server->soket->write(" ");
                igra->server->soket->write((std::to_string(x() + POLOVINA_SIRINE_KULE + 500).c_str()));
                igra->server->soket->write("-");
                igra->server->soket->write((std::to_string(y() + POLOVINA_SIRINE_KULE + 500).c_str()));
                igra->server->soket->write(" ");
                igra->server->soket->write((std::to_string(projektil->getID()).c_str()));
                igra->server->soket->write(" ");
                igra->server->soket->write((std::to_string(ugao).c_str()));
                igra->server->soket->write(" ");
                igra->server->soket->waitForBytesWritten(1000);
            }

            if(igra->server->imaKorisnika()) {
                igra->server->soket->write("objekat_kraj");
                igra->server->soket->flush();
                igra->server->soket->waitForBytesWritten(1000);
            }
        }
        if(++redniBroj > 7){
            tajmer2->disconnect();
            redniBroj = 0;
        }
    }
}


void KulaTop::pronadjiMetu(){
    QList<QGraphicsItem *> objektiUDometu = domet->collidingItems();

    metaPronadjena = false;

    double najkraceRastojanje = 300;
    QPointF najblizaTacka(0,0);
    for (size_t i = 0, n = objektiUDometu.size(); i < n; ++i){

        Neprijatelj * neprijatelj = dynamic_cast<Neprijatelj *>(objektiUDometu[i]);

        if (neprijatelj){
            double ovoRastojanje = rastojanje(objektiUDometu[i]);
            if (ovoRastojanje < najkraceRastojanje){
                najkraceRastojanje = ovoRastojanje;
                najblizaTacka = objektiUDometu[i]->pos();
                metaPronadjena = true;
            }
        }
    }

    if (metaPronadjena){
        meta.setX(najblizaTacka.x() + 48);
        meta.setY(najblizaTacka.y() + 48);
        connect(tajmer2,SIGNAL(timeout()),this,SLOT(pucaj()));
        tajmer2->start(100);
    }
}

int KulaTop::identifikacijaKula(){
    return 1;
}

int KulaTop::getPrecnikDometa()
{
    return PRECNIK_KRUGA_DOMETA;

}

int KulaTop::getPolovinaSirine()
{
    return POLOVINA_SIRINE_KULE;
}

QGraphicsEllipseItem *KulaTop::getDomet()
{
    return domet;
}

void KulaTop::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::RightButton) {
        domet->setOpacity(1);
    }
    qDebug () << "k:";
}

void KulaTop::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    domet->setOpacity(0);
}
