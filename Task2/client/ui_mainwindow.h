/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_5;
    QPushButton *butDisconnect;
    QPushButton *butConnect;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *lConnectionIndicator;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_6;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *lFreeMem;
    QLabel *label_3;
    QLabel *lPCNeme;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QLabel *lTime;
    QSpacerItem *verticalSpacer_3;
    QLabel *lAllMem;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 563);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        butDisconnect = new QPushButton(centralwidget);
        butDisconnect->setObjectName(QString::fromUtf8("butDisconnect"));

        gridLayout_5->addWidget(butDisconnect, 1, 1, 1, 1);

        butConnect = new QPushButton(centralwidget);
        butConnect->setObjectName(QString::fromUtf8("butConnect"));

        gridLayout_5->addWidget(butConnect, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(250, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        lConnectionIndicator = new QLabel(centralwidget);
        lConnectionIndicator->setObjectName(QString::fromUtf8("lConnectionIndicator"));
        lConnectionIndicator->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(lConnectionIndicator, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 1, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_4, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_6->addItem(verticalSpacer_2, 0, 3, 1, 1);

        lFreeMem = new QLabel(centralwidget);
        lFreeMem->setObjectName(QString::fromUtf8("lFreeMem"));
        lFreeMem->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lFreeMem, 2, 3, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_3, 1, 1, 1, 1);

        lPCNeme = new QLabel(centralwidget);
        lPCNeme->setObjectName(QString::fromUtf8("lPCNeme"));
        lPCNeme->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lPCNeme, 2, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_5, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_6, 1, 4, 1, 1);

        lTime = new QLabel(centralwidget);
        lTime->setObjectName(QString::fromUtf8("lTime"));
        lTime->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lTime, 2, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_6->addItem(verticalSpacer_3, 3, 3, 1, 1);

        lAllMem = new QLabel(centralwidget);
        lAllMem->setObjectName(QString::fromUtf8("lAllMem"));
        lAllMem->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(lAllMem, 2, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_6, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        butDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        butConnect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Connection", nullptr));
        lConnectionIndicator->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "All Mem", nullptr));
        lFreeMem->setText(QApplication::translate("MainWindow", "3", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "PC Name", nullptr));
        lPCNeme->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Free Mem", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Updated", nullptr));
        lTime->setText(QApplication::translate("MainWindow", "4", nullptr));
        lAllMem->setText(QApplication::translate("MainWindow", "2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
