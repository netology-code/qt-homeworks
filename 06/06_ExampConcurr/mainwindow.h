#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
#include <algorithm>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Метод считывает данные из исходного файла
    QVector<uint32_t> ReadFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> ProcessFile(QVector<uint32_t> dataFile);
    //Метод ищет Максимумы
    QVector<double> FindMax(QVector<double> resultData);
    //Метод ищет минимумы
    QVector<double> FindMin(QVector<double> resultData);
    //Метод отображает результаты
    void DisplayResult(QVector<double> mins, QVector<double> maxs);




private slots:
    void on_pb_path_clicked();
    void on_pb_start_clicked();



private:
    Ui::MainWindow *ui;
    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;

    QVector<uint32_t> readData;
    QVector<double> processData;
    QVector<double> mins, maxs;
    uint32_t pBarVal = 0;




    QFuture<QVector<uint32_t>> futReadData;
    QFuture<QVector<double>> futProcData;
    QFuture<QVector<double>> futFindMins;
    QFuture<QVector<double>> futFindMax;

    QFutureWatcher<QVector<uint32_t>> whFutReadData;
    QFutureWatcher<QVector<double>> whFutProcData;
    QFutureWatcher<QVector<double>> whFindMins;
    QFutureWatcher<QVector<double>> whFindMax;

};
#endif // MAINWINDOW_H
