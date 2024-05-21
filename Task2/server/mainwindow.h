#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>

#include "TCPConnection.h"
#include "SendHDDInfo.h"

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

    cConnection server;
    cHddInfo info;
    QTimer timerToSent;
    QTimer timerToDel;

private slots:
    void startSending();
    void stopTimer();
    void setInfo();
    void on_bDisc_clicked();
    void updateList();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
