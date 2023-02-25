#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

#define NUM_DATA_FOR_CONNECT_TO_DB 5


enum fieldsForConnect{

    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4

};


enum answersType{

    requestAllFilms = 1,
    requestComedy = 2,
    requestHorrors = 3

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    bool ConnectToDataBase(QVector<QString> dataForConnect);
    void DisconnectFromDataBase(QString nameDb = "");
    QSqlError RequestToDB(QString request);
    QSqlError GetLastError(void);


signals:




private:

    QSqlDatabase* dataBase;




};

#endif // DATABASE_H
