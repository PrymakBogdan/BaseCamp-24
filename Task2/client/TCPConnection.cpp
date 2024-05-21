#include "TCPConnection.h"

cConnection::cConnection(){}

cConnection::~cConnection(){}

bool cConnection::startServer()
{
    if(this->listen(QHostAddress::Any, PORT_TO_CONNECT))
    {
        qDebug()<<"Server started";
        return true;
    }
    else
    {
        qDebug()<<"Error listening";
        return false;
    }
}

void cConnection::incomingConnection(qintptr sockDesc)
{
    socket = new QTcpSocket(this);
    if(socket -> setSocketDescriptor(sockDesc))
    {
        connect(socket, &QTcpSocket::readyRead, this, &cConnection::sockReady);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        vSockets.push_back(socket);
        sockIndexToSend.push_back(sockDesc);
        socket->waitForReadyRead(500);
        QString sockName = strDate;

        if (checkState(sockName, socket))
        {
            sockState.socketIndex.push_back(sockDesc);
            sockState.socketName.push_back(sockName);
            sockState.socketState.push_back(true);
            qDebug()<<"connected socket"<< sockState.socketIndex.last()<<" " << sockState.socketName.last()<<" "<<sockState.socketState.last();
        }
    }
}


bool cConnection::conClient()
{
    try
    {
        socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::readyRead, this, &cConnection::sockReady);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        qDebug()<<"connecting to host";
        return true;
    }
    catch(const std::exception& e)
    {
        qDebug()<<"not connected";
        return false;
    }

}

QString cConnection::sockReady()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    if(in.status()==QDataStream::Ok)
    {
        strDate.clear();
        in>>strDate;
        qDebug()<<"msg readed"<<strDate;
        return strDate;
    }

    qDebug()<<"msg not readed";
    return 0;
}

bool cConnection::sockDisc()
{
    try
    {
        socket->deleteLater();
        qDebug()<<"Socket deleted";
        socket = nullptr;
        return true;
    }
    catch (const std::exception& e)
    {
        qDebug()<<"Socket not deleted";
        return false;
    }
}

bool cConnection::conClToHost()
{
    socket->connectToHost(ADDR_TO_CONNECT, PORT_TO_CONNECT);
    if (socket->waitForConnected(500))
    {
        qDebug()<<"connected to host";
        return true;
    }
    else
    {
        qDebug()<<"not connected to host";
        return false;
    }
}

void cConnection::sendStringToHost(const QString &msg) {
    if (socket != nullptr && socket->state() == QAbstractSocket::ConnectedState) {
        dataBuf.clear();
        QDataStream outData(&dataBuf, QIODevice::WriteOnly);
        outData.setVersion(QDataStream::Qt_5_12);
        outData<<msg;
        socket->write(dataBuf);
        if (socket->waitForBytesWritten(THREE_SEC))
        {
            qDebug() << "Message sent to host";
        } else {
            qDebug() << "Failed to send" << socket->errorString();
        }
    } else {
        qDebug() << "Socket is not connected";
    }
}

bool cConnection::SendToClient(const QString &msg)
{
    if(!vSockets.empty() && !socket->disconnect())
    {
        dataBuf.clear();
        QDataStream outData(&dataBuf, QIODevice::WriteOnly);
        outData.setVersion(QDataStream::Qt_5_12);
        outData<<msg;
        socket->write(dataBuf);
        qDebug()<<"sended to "<<socket->socketDescriptor();
        return true;
    }
    else
    {
        qDebug()<<"not sended to "<<socket->socketDescriptor();
        return false;
    }
}

bool cConnection::SendToAllClients(const QString &msg)
{
    if(!vSockets.empty())
    {
        dataBuf.clear();
        QDataStream outData(&dataBuf, QIODevice::WriteOnly);
        outData.setVersion(QDataStream::Qt_5_12);
        outData<<msg;
        int vSocketsSize = vSockets.size();
        for(int i = 0;i<  vSocketsSize; i++)
        {
            if(!vSockets.empty())
            {
                if (isSocketConnected(vSockets[i]))
                {
                    vSockets[i]->write(dataBuf);
                    qDebug()<<"sended to"<<vSockets[i];
                }
                else
                {
                    vSockets.removeOne(vSockets[i]);
                    qDebug()<<"Removed socket"<< sockIndexToSend[i];


                    for (int j = 0; j < sockState.socketIndex.size();j++)
                    {
                        if(sockState.socketIndex[j] == sockIndexToSend[i])
                        {
                            sockState.socketState[j] = false;
                            qDebug()<<"checking for 1 min";
                            int q = sockState.socketIndex[j];
                            checkDelList(q);
                        }
                    }

                    sockIndexToSend.removeOne(sockIndexToSend[i]);

                    if (vSocketsSize > 0)
                        vSocketsSize--;
                    else
                        break;
                }
            }
            else
                break;
        }
        return true;
    }
    else
    {
        qDebug()<<"not sended, no connected clients";
        return false;
    }
}

void cConnection::checkDelList(const int index)
{
    qDebug()<<"the index being checked"<<index;
    QTimer::singleShot(ONE_MIN, this, [this, index]() {
            for (int ind=0; ind < sockState.socketIndex.size(); ind++)
            {
                if(sockState.socketIndex[ind] == index)
                {
                    qDebug()<<"Go to remove socketIndex "<<sockState.socketIndex[ind];
                    qDebug()<<"Go to remove sockIndexToSend "<<index;
                    if(sockState.socketState[ind] == false)
                    {
                        sockState.socketIndex.remove(ind);
                        sockState.socketName.remove(ind);
                        sockState.socketState.remove(ind);
                        qDebug()<<index<<" deleted";
                        break;
                    }
                    else
                        qDebug()<<index<<"not deleted";
                }
            }
        });
}

bool cConnection::isSocketConnected(QTcpSocket *socket)
{
    if (socket != nullptr)
    {
        return socket->state() == QAbstractSocket::ConnectedState;
    }
    return false;
}

bool cConnection::isClientConnected(QTcpSocket *socket)
{
    if (socket != nullptr) {
        return socket->isOpen() && socket->state() == QAbstractSocket::ConnectedState;
    }
    return false;
}

bool cConnection::checkState(const QString &sockName, QTcpSocket *socket)
{
    for(int i=0; i<this->sockState.socketName.size();i++)
    {
        qDebug()<<this->sockState.socketName[i];
        if (this->sockState.socketName[i] == sockName && this->sockState.socketState[i] == 1)
        {
            qDebug()<<"Socket is not connected name: "<<sockName;
            sockDisc();

            qDebug()<<"Removed in check vSockets" << vSockets.last();

            socket->disconnect();
            vSockets.removeLast();
            sockIndexToSend.removeLast();

            return false;
        }
        else if(this->sockState.socketName[i] == sockName && this->sockState.socketState[i] == 0)
        {
            qDebug()<<"Socket is reconnected"<<socket->socketDescriptor();
            this->sockState.socketState[i] = true;
            this->sockState.socketIndex[i] = socket->socketDescriptor();
            return false;
        }

    }
    qDebug()<<"connection is ok";
    return true;
}
