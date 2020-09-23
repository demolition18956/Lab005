#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uSocket = new QUdpSocket(this);

    uSocket->bind(5678);

    connect(uSocket, &QUdpSocket::readyRead, this, &MainWindow::processMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processMessage()
{
    QByteArray datagram;

    while (uSocket->hasPendingDatagrams())
    {
        datagram.resize(uSocket->pendingDatagramSize());
        uSocket->readDatagram(datagram.data(), datagram.size());
    }

    QString msg;
    QTextStream in(&datagram, QIODevice::ReadOnly);

    msg = in.readLine();
    ui->textEdit->append(msg);
}
