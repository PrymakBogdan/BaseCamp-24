#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H




#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QTimer>

#define PORT_TO_CONNECT 5555
#define ADDR_TO_CONNECT "127.0.0.1"
#define THREE_SEC 3000
#define FIVE_SEC 5000
#define ONE_MIN 60000


class cConnection: public QTcpServer
{
    Q_OBJECT
private:

    QVector <QTcpSocket*> vSockets;
    QVector <QString> vSocketsName;
    QByteArray dataBuf;
    QVector <qintptr> sockIndexToSend;

public:
    cConnection();
    ~cConnection();

    QTcpSocket* socket = nullptr;
    QString strDate;
    struct socketsState
    {
        QVector <qintptr> socketIndex;
        QVector <QString> socketName;
        QVector <bool> socketState;
    }sockState;

    bool startServer();
    void incomingConnection(qintptr sockDesc);
    bool conClient();
    QString sockReady();
    bool sockDisc();
    bool conClToHost();
    bool SendToClient(const QString &msg);
    bool SendToAllClients(const QString &msg);
    bool isSocketConnected(QTcpSocket *socket);
    bool isClientConnected(QTcpSocket *socket);
    void sendStringToHost(const QString &msg);
    bool checkState(const QString &sockName, QTcpSocket *socket);
    void checkDelList(const int index);
};

#endif // TCPCONNECTION_H
