#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * Выделяем память под объект UdpWorker. И сразу инициализируем сокет.
    */
    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();


    /*
     * Выделяем память под таймер
    */
    timer = new QTimer(this);


    /*
     * Необходимо раз в секунду отправлять данные. Опишем это в лямбда функции и
     * соеденим с сигналом timeout. В функции будем получать дату и время и
     * отправлять их при помощи SendDatagram
    */
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();
        QByteArray dataToSend;
        QDataStream outStream(&dataToSend, QIODevice::WriteOnly);
        outStream << dateTime;
        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });

    /*
     * Для приема данных необходимо соединить сигнал от UdpWorker со слотом отображающим данные
    */
    connect(udpWorker, &UDPworker::sig_sendDataToGUI, this, &MainWindow::DisplayRcvDataTime);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Обработчкик кнопки "Начать передачу"
 */
void MainWindow::on_pb_start_clicked()
{
    //Просто запускаем таймер
    timer->start(TIMER_DELAY);
}

/*!
 * \brief Слот отображает принятые данные в лог
 * \param data - принятые дата и время
 */
void MainWindow::DisplayRcvDataTime(QDateTime data)
{

    counterPck++;

    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
}

/*!
 * \brief Обработчик кнопки "Остановить передачу".
 */
void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

