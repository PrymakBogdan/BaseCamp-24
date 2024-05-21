#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TCPConnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::setInfo()
{
    if(clientSock.strDate != nullptr )
    {
        if(clientSock.isClientConnected(clientSock.socket))
        {
            QStringList splitList = clientSock.strDate.split(" ");
            ui->lPCNeme->setText(splitList[0]);
            ui->lAllMem->setText(splitList[1]);
            ui->lFreeMem->setText(splitList[2]);

            QDateTime currentDateTime = QDateTime::currentDateTime();
            ui->lTime->setText(currentDateTime.toString("HH:mm:ss"));
            return true;
        }
        else
        {
            stopTimer();
            ui->lConnectionIndicator->setStyleSheet("QLabel { background-color : red; }");
            return false;
        }
    }
    else
    {
        qDebug()<<"Empty strDate";
        return false;
    }
    return false;
}

void MainWindow::startTimer()
{
    QObject::connect(&timer, &QTimer::timeout,this, &MainWindow::setInfo);
    timer.start(FIVE_SEC);
}

void MainWindow::stopTimer()
{
    timer.stop();
}

void MainWindow::on_butConnect_clicked()
{
    if (!clientSock.isSocketConnected(clientSock.socket))
    {
        bool notEmpty;
        QString clientName;

        clientName = QInputDialog::getText(nullptr, "Input Dialog", "Enter your name:", QLineEdit::Normal, QString(), &notEmpty);;

        qDebug()<<"msg: "<<clientName;
        clientSock.conClient();
        if (notEmpty && !clientName.isEmpty() && clientSock.conClToHost() == true)
        {
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setText("wait a couple of seconds, if not connected, try to changing the name");

            msgBox->show();

            clientSock.sendStringToHost(clientName);

            if(!clientSock.socket->waitForDisconnected(5000))
            {
                ui->lConnectionIndicator->setStyleSheet("QLabel { background-color : green; }");
                startTimer();
            }
            else clientSock.sockDisc();
        }

    }
}

void MainWindow::on_butDisconnect_clicked()
{
    if(clientSock.isSocketConnected(clientSock.socket))
    {
        clientSock.sockDisc();
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setText("wait a couple of seconds, disconnection in progress");

        msgBox->show();
    }
    stopTimer();
    ui->lConnectionIndicator->setStyleSheet("QLabel { background-color : red; }");
}
