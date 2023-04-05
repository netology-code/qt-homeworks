#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_path->setText("C:/Netology/QtLesson/testData.adc");
    pathToFile = ui->le_path->text();

    pBarVal = 0;






}

MainWindow::~MainWindow()
{
    delete ui;
}



/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel)
{

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }
    else{

        //продумать как выйти из функции
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;

        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;

            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;

                if(sizeFrame > 1500){
                    continue;
                }

                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;

                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);

                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(const QVector<uint32_t> dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }

        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);
    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
  //  QThread::sleep(1);
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }

    //Поиск 2го максимума
   // QThread::sleep(1);
    foreach (double num, resultData){
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> resultData)
{

    double min = 0, sMin = 0;
    //QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
   // QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;

}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}


/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked()
{
    pathToFile = "";
    ui->le_path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                              tr("Открыть файл"), "/home/", tr("ADC Files (*.adc)"));

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked()
{
    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){

        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);

    int selectIndex = ui->cmB_numCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEB;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xEC;
    }





//    readData = ReadFile(pathToFile, numberSelectChannel);
//    processData = ProcessFile(readData);
//    maxs = FindMax(processData);
//    mins = FindMin(processData);
//    DisplayResult(mins, maxs);




    /*Qt Concurrent */


    /*Модуль Qt Concurrent
     является высокоуровневым  API,
     который позволяют писать многопоточные программы без использования низкоуровневых примитивов,
     таких как мьютексы, блокировки чтения-записи, условия ожидания или семафоры.
    */

    /*QFuture
     это контейнер для хранения результатов вычисления другого потока
    */


//    futReadData = QtConcurrent::run(&MainWindow::ReadFile, this, pathToFile, numberSelectChannel);
//    whFutReadData.setFuture(futReadData);

//    connect(&whFutReadData, &QFutureWatcher<QVector<uint32_t>>::finished, this, [&]{
//        readData = futReadData.result();
//        futProcData = QtConcurrent::run(&MainWindow::ProcessFile, this, readData);
//        whFutProcData.setFuture(futProcData);
//    });

//    connect(&whFutProcData, &QFutureWatcher<QVector<double>>::finished, this, [&]{
//        processData = futProcData.result();
//        futFindMins = QtConcurrent::run(&MainWindow::FindMin, this, processData);
//        whFindMins.setFuture(futFindMins);
//    });

//    connect(&whFindMins, &QFutureWatcher<QVector<double>>::finished, this, [&]{
//        mins = futFindMins.result();
//        futFindMax = QtConcurrent::run(&MainWindow::FindMax, this, processData);
//        whFindMax.setFuture(futFindMax);

//        ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
//        ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

//    });

//    connect(&whFindMins, &QFutureWatcher<QVector<double>>::finished, this, [&]{
//        maxs = futFindMax.result();
//        ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
//        ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
//    });





    auto reads = [&]{ return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return ProcessFile(res); };
    auto finds = [&](QVector<double> res){ mins = FindMin(res);
                                           maxs = FindMax(res);
                                            DisplayResult(mins, maxs);};

    QtConcurrent::run(reads).then(process).then(finds);







}

