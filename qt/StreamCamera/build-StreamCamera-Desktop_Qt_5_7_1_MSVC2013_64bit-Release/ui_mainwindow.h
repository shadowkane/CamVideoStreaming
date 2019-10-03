/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *CameraArea;
    QPushButton *btn_startStreaming;
    QComboBox *comboBox_sourceImageFormat;
    QLabel *label;
    QPushButton *btn_stopStreaming;
    QLabel *label_2;
    QSpinBox *spinBox_port;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(660, 641);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CameraArea = new QLabel(centralWidget);
        CameraArea->setObjectName(QStringLiteral("CameraArea"));
        CameraArea->setEnabled(true);
        CameraArea->setGeometry(QRect(10, 10, 640, 480));
        CameraArea->setFrameShape(QFrame::Box);
        CameraArea->setTextFormat(Qt::AutoText);
        btn_startStreaming = new QPushButton(centralWidget);
        btn_startStreaming->setObjectName(QStringLiteral("btn_startStreaming"));
        btn_startStreaming->setGeometry(QRect(10, 550, 151, 31));
        comboBox_sourceImageFormat = new QComboBox(centralWidget);
        comboBox_sourceImageFormat->setObjectName(QStringLiteral("comboBox_sourceImageFormat"));
        comboBox_sourceImageFormat->setGeometry(QRect(450, 550, 121, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 510, 211, 31));
        QFont font;
        font.setPointSize(17);
        label->setFont(font);
        btn_stopStreaming = new QPushButton(centralWidget);
        btn_stopStreaming->setObjectName(QStringLiteral("btn_stopStreaming"));
        btn_stopStreaming->setEnabled(false);
        btn_stopStreaming->setGeometry(QRect(170, 550, 151, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 510, 101, 31));
        QFont font1;
        font1.setPointSize(21);
        label_2->setFont(font1);
        spinBox_port = new QSpinBox(centralWidget);
        spinBox_port->setObjectName(QStringLiteral("spinBox_port"));
        spinBox_port->setGeometry(QRect(171, 511, 151, 31));
        spinBox_port->setMaximum(645000);
        spinBox_port->setValue(27015);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        CameraArea->setText(QString());
        btn_startStreaming->setText(QApplication::translate("MainWindow", "Start Streaming", Q_NULLPTR));
        comboBox_sourceImageFormat->clear();
        comboBox_sourceImageFormat->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "BGR", Q_NULLPTR)
        );
        label->setText(QApplication::translate("MainWindow", "Select source format", Q_NULLPTR));
        btn_stopStreaming->setText(QApplication::translate("MainWindow", "Stop Streaming", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Port:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
