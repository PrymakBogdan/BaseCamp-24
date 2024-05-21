#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    server.startServer();
    startSending();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInfo()
{
    info.setName();
    info.setInfo();
    ui->lName->setText(info.getPCName());
    ui->lAll->setText(info.getAllMem());
    ui->lFree->setText(info.getFreeMem());

    QString strToSend = info.getPCName() + " " + info.getAllMem() + " " + info.getFreeMem();
    server.SendToAllClients(strToSend);
    updateList();
}

void MainWindow::startSending()
{
    QObject::connect(&timerToSent, &QTimer::timeout,this, &MainWindow::setInfo);

    timerToSent.start(FIVE_SEC);
}

void MainWindow::stopTimer()
{
    timerToSent.stop();
}


void MainWindow::on_bDisc_clicked()
{

}

void  MainWindow::updateList()
{
    QStandardItemModel* model = new QStandardItemModel();

    int rows = server.sockState.socketIndex.size();
    int columns = 3;
    model->setRowCount(rows);
    model->setColumnCount(columns);
    model->setHorizontalHeaderItem(0,new QStandardItem("ID"));
    model->setHorizontalHeaderItem(1,new QStandardItem("Name"));
    model->setHorizontalHeaderItem(2,new QStandardItem("State"));

    for (int row = 0; row < rows; ++row) {
        if (row < server.sockState.socketIndex.size())
        {
            QStandardItem* item = new QStandardItem(QString::number(server.sockState.socketIndex[row]));
            item->setEditable(false);
            model->setItem(row, 0, item);
        }
        else
        {
            QStandardItem* item = new QStandardItem("");
            item->setEditable(false);
            model->setItem(row, 0, item);
        }

        if (row < server.sockState.socketName.size())
        {
            model->setItem(row, 1, new QStandardItem(server.sockState.socketName[row]));
        }
        else
        {
            QStandardItem* item = new QStandardItem("");
            item->setEditable(false);
            model->setItem(row, 1, item);
        }

        if (row < server.sockState.socketState.size())
        {
            if (server.sockState.socketState[row] == true)
            {
                QStandardItem* item = new QStandardItem("Connected");
                item->setEditable(false);
                model->setItem(row, 2, item);
            }
            else
            {
                QStandardItem* item = new QStandardItem("Disconnected");
                item->setEditable(false);
                model->setItem(row, 2, item);
            }
        }
        else
        {
            QStandardItem* item = new QStandardItem("");
            item->setEditable(false);
            model->setItem(row, 2, item);
        }
    }
    ui->tClientList->setModel(model);
}
