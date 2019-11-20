#include "Klijent.h"
#include <QInputDialog>
#include "Igra.h"

extern Igra * igra;

Klijent::Klijent(QObject *roditelj) : QObject(roditelj) {
    putUcitan = false;
    objekatUcitan = false;
}

void Klijent::Test() {
    soket = new QTcpSocket(this);

    connect(soket,SIGNAL(connected()), this, SLOT(povezan()));
    connect(soket,SIGNAL(disconnected()), this, SLOT(vezaIzgubljena()));
    connect(soket,SIGNAL(readyRead()), this, SLOT(citanjePuta()));

    qDebug() << "Povezivanje...";

    bool ok;
    QString niska = QInputDialog::getText(NULL, tr("QInputDialog::getText()"), tr("Ip:port:"), QLineEdit::Normal, 0, &ok);
    if(!ok)
    {
        exit( 0 );
    }
    QStringList lista = niska.split(":");
    soket->connectToHost(lista[0], lista[1].toInt());

    if(!soket->waitForConnected(5000)) {
       qDebug() << "Greska: " <<  soket->errorString();
    }
}

QString Klijent::vratiPoruku() {
    return poruka;
}

bool Klijent::putJeUcitan() {
    return putUcitan;
}

bool Klijent::objekatJeUcitan() {
    return objekatUcitan;
}

void Klijent::povezan() {
    qDebug() << "Povezan!";
}

void Klijent::vezaIzgubljena() {
    qDebug() << "Veza prekinuta!";
}

void Klijent::citanjePuta() {
    if(!putUcitan) {
        poruka.append(soket->readAll());
        if(poruka.endsWith("put_kraj")) {
            putUcitan = true;
            qDebug() << "Put je ucitan";
            emit ucitanPut();
            poruka.clear();
            disconnect(soket,SIGNAL(readyRead()), this, SLOT(citanjePuta()));
            connect(soket,SIGNAL(readyRead()), this, SLOT(citanje()));
        }
    }
}

void Klijent::citanje() {
    poruka.append(soket->readAll());
    if (poruka.endsWith("objekat_kraj")) {
        qDebug() << "Objekat je ucitan";
        emit ucitanObjekat();
        poruka.clear();
    }
}
