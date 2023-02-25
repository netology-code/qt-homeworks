#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendDataToGUI, this, &MainWindow::PorcessReceiveData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]{

        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        dataToSend.resize(sizeof(dateTime));

        memcpy(dataToSend.data(), &dateTime, sizeof(dateTime));
        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::PorcessReceiveData(QByteArray data)
{
    counterPck++;
    QDateTime rcvDateTime;
    memcpy(&rcvDateTime, data.data(), sizeof(rcvDateTime));

    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + rcvDateTime.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

