#ifndef KLIJENT_H
#define KLIJENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QString>

class Klijent : public QObject {
    Q_OBJECT

public:
    explicit Klijent(QObject *roditelj = 0);
    void Test();
    QString vratiPoruku();
    bool putJeUcitan();
    bool objekatJeUcitan();
    QTcpSocket *soket;

signals:
    void ucitanPut();
    void ucitanObjekat();

public slots:
    void povezan();
    void vezaIzgubljena();
    void citanjePuta();
    void citanje();

private:
    QString poruka;
    bool putUcitan;
    bool objekatUcitan;
};

#endif // KLIJENT_H
