#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    myServer(this)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnectionHandler(){
    QTcpSocket *client = myServer.nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(readDataHandler()));
    //connect(client, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSoc));
    qDebug() << this << "new connection detected";
}

void MainWindow::readDataHandler(){
    QTcpSocket *clientSocket = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = clientSocket->readAll();
    QList<QByteArray> info = data.split('=');
    if(static_cast<QString>(info[0]).compare("imageConfig")==0) {
        QList<QByteArray> str = info[1].split('|');
        //qDebug() << this << "image width";
        imageW=atoi(str[0]);
        //qDebug() << this << "image height";
        imageH=atoi(str[1]);
        //qDebug() << this << "image channels";
        imageFormat=atoi(str[2]);
        imageSize = imageW * imageH * imageFormat;
        imageStep = imageW * imageFormat;
        imageData.resize(imageSize);
        ui->CameraArea->setGeometry(10,10,imageW, imageH);
    }
    else if(static_cast<QString>(info[0]).compare("imageData")==0) {
        //qDebug() << this << "start receive image data";
        receivingImage = 1;
        imageData.clear();
        imageData.append(static_cast<QByteArray>(info[1]));
    }
    else if(receivingImage == 1){
        //qDebug() << this << "other image data";
        imageData.append(data);
        //qDebug() << this << QString::number(static_cast<double>(imageSize));
        //qDebug() << this << QString::number(imageData.size());
        if(imageData.size() == imageSize){
            receivingImage = 0;
            BGR2RGB(&imageData);
            ui->CameraArea->setPixmap(QPixmap::fromImage(QImage(reinterpret_cast<unsigned char*>(imageData.data()), imageW, imageH, imageStep, QImage::Format_RGB888)));
            //qDebug() << this << "end receive image data";
        }
    }
    //qDebug() << this << "reading data";
}

void MainWindow::BGR2RGB(QByteArray *image) {
    unsigned char c;
    for(int i=0; i<(image->size()); i+=3) {
        c = (*image)[i];
        (*image)[i] = (*image)[i+2];
        (*image)[i+2] = c;
    }
}

void MainWindow::on_btn_startStreaming_clicked()
{
    myServer.listen(QHostAddress::Any, ui->spinBox_port->value());
    connect(&myServer, SIGNAL(newConnection()), this, SLOT(newConnectionHandler()));
    startStream(true);
}


void MainWindow::on_btn_stopStreaming_clicked()
{
    myServer.close();
    startStream(false);
}


void MainWindow::startStream(bool start) {
    switch (start) {
    case true:
        ui->btn_startStreaming->setEnabled(false);
        ui->btn_stopStreaming->setEnabled(true);
        break;
    case false:
        ui->btn_startStreaming->setEnabled(true);
        ui->btn_stopStreaming->setEnabled(false);
        break;
    default:
        break;
    }
}

