#include "Server.h"

Server::Server(QObject *roditelj) : QObject(roditelj) {
    server = new QTcpServer(this);
    imaKor = false;

    connect(server,SIGNAL(newConnection()),this,SLOT(novaKonekcija()));

    if(!server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server nije mogao da startuje!";
    }
    else {
        qDebug() << "Server poceo sa radom!";
    }
    //server->waitForNewConnection(10000);
}

Server::~Server() {
    //delete soket;
    delete server;
}

bool Server::imaKorisnika() {
    return imaKor;
}

QString Server::vratiPoruku() {
    return poruka;
}

void Server::novaKonekcija() {
    imaKor = true;

    soket = server->nextPendingConnection();

    connect(soket,SIGNAL(readyRead()), this, SLOT(citanje()));
}

void Server::citanje() {
    qDebug() << "Server cita...";
    poruka.append(soket->readAll());
    if (poruka.endsWith("kraj_poruke")) {
        qDebug() << "Poruka je ucitana";
        emit ucitanaPoruka();
        poruka.clear();
    }
}
