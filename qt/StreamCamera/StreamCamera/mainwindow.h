#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newConnectionHandler();
    void readDataHandler();

private slots:
    void on_btn_startStreaming_clicked();

    void on_btn_stopStreaming_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer myServer;

    int imageW;
    int imageH;
    int imageFormat;
    double imageSize;
    double imageStep;
    QByteArray imageData;
    int receivingImage;

    void BGR2RGB(QByteArray *image);
    void startStream(bool start);
};

#endif // MAINWINDOW_H
