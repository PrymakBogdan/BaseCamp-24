#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include "TCPConnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cConnection clientSock;
    QTimer timer;

private slots:

    void startTimer();
    void stopTimer();
    bool setInfo();
    void on_butConnect_clicked();

    void on_butDisconnect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
