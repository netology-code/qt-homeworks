#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);

    dataDb = new DbData(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);


    //Сразу добавляем драйвер БД, Имя используем "по умолчанию"
    dataBase->AddDataBase("QPSQL");

    /*
     * Устанавливаем данные для подключениея к БД.
     * Поскольку метод небольшой используем лямбда-функцию.
     */
    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });


    ///Код ДЗ, соединение сигналов со слотами.
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered()
{
    dataDb->show();
}

/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */

void MainWindow::on_act_connect_triggered()
{
    if(ui->lb_statusConnect->text() == "Отключено"){

        bool connectStatus = false;

        connectStatus =  dataBase->ConnectToDataBase(dataForConnect);

        if(connectStatus){

            ui->act_connect->setText("Отключиться");
            ui->lb_statusConnect->setText("Подключено к БД");
            ui->lb_statusConnect->setStyleSheet("color:green");
            ui->pb_request->setEnabled(true);
        }
        else{

            dataBase->DisconnectFromDataBase();
            msg->setIcon(QMessageBox::Critical);
            msg->setText(dataBase->GetLastError().text());
            msg->exec();

        }

    }
    else{

        dataBase->DisconnectFromDataBase();
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
    }
}

/*!
 * \brief Обработчик кнопки "Получить"
 */
void MainWindow::on_pb_request_clicked()
{

    ///Тут должен быть код ДЗ

}

/*!
 * \brief Слот отображает значение в QTableWidget
 * \param widget
 * \param typeRequest
 */
void MainWindow::ScreenDataFromDB(QTableWidget *widget, int typeRequest)
{

    ///Тут должен быть код ДЗ

}
