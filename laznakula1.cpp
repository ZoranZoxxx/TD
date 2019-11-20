#include "laznakula1.h"
#include <QTimer>
#include "Projektil.h"
#include "Igra.h"
#include "Neprijatelj.h"
#include <math.h>

extern Igra * igra;

LaznaKula1::LaznaKula1(QPointF pozicija, int id, QGraphicsItem *roditelj)
    : LaznaKula(pozicija, id) /* MZ*/{

    this->id = id;

    setPos(pozicija);

    // zvuk
    zvukStrele = new QMediaPlayer();
    zvukStrele->setMedia(QUrl("qrc:/1/strela.wav"));

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
            }                        //:/slike/slike/spear catapult/shooting nw0000.png
            QString putanja = QString(":/slike/slike/spear catapult/shooting %00000%1.png").arg(smer).arg(j);
            //qDebug() << putanja;
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
    domet->setPen(QPen(Qt::DotLine));


    meta = QPointF(0,0);
    metaPronadjena = false;

    connect(tajmer,SIGNAL(timeout()),this,SLOT(pronadjiMetu()));
    tajmer->start(300);
}

void LaznaKula1::pucaj(){

    if (igra->rezimPauze != 1){
        QLineF ln(QPointF(x()+POLOVINA_SIRINE_KULE,y()+POLOVINA_SIRINE_KULE),meta);

        setPixmap(QPixmap(matricaSlika[(int)(ln.angle()) / 45][redniBroj]));
        setTransformOriginPoint(POLOVINA_SIRINE_KULE, POLOVINA_SIRINE_KULE);
        setRotation(-1 * ((int)(ln.angle()) % 45));


        if(++redniBroj > 7){
            tajmer2->disconnect();
            redniBroj = 0;
        }
    }
}


void LaznaKula1::pronadjiMetu(){
    QList<QGraphicsItem *> objektiUDometu = domet->collidingItems();

    metaPronadjena = false;

    double najkraceRastojanje = 300;
    QPointF najblizaTacka(0,0);
    for (size_t i = 0, n = objektiUDometu.size(); i < n; ++i){

        LazniNeprijatelj * lazniNeprijatelj = dynamic_cast<LazniNeprijatelj *>(objektiUDometu[i]);

        if (lazniNeprijatelj){
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

//int LaznaKula1::identifikacijaKula(){//m
//    return 1;//m
//}



