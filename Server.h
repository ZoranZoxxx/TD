#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject *roditelj = 0);
    ~Server();
    bool imaKorisnika();
    QTcpSocket *soket;
    QString vratiPoruku();

signals:
    void ucitanaPoruka();

public slots:
    void novaKonekcija();
    void citanje();

private:
    bool imaKor;
    QTcpServer *server;
    QString poruka;
};

#endif // SERVER_H
