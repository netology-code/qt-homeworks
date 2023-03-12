#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{


    /* QUdpSocket
     * За прием передачу данных по протоколу UDP в Qt отвечает класс QUdpSocket.
     * Каждый экземпляр этого класса может прослушивать один порт и один аждрес
     * на который он ожидает приема данных. Класс наследован от QObject поэтому
     * поддерживает механизм слотов/сигналов и иерархии.
    */
    serviceUdpSocket = new QUdpSocket(this);



    /* bind
     * Для того чтобы сокет начал прослушивать порт используется метод bind(QhostAddres, порт).
     * В котором первым параметром передается адрес, на который сокет ожидает приема данных
     * и с которого будет отправлять данные и вторым порт, на который будет ожидать приема данных.
     * Порты созданы для разделения разных приложений на одном IP адресе.
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    /* readyRead
     * При получении новых данных из сети сокет испускает сигнал readyReed.
     * Который должен быть соединен с обработчиком датаграммы
    */
    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::ReadPendingDatagrams);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    /*
     * Данные в датаграмме передаются в QByteArray. Т.е. для отправки
     * данных их необходимо сериализовать, для получения десериализовать.
     * Обычно для сервисных и для пользовательских данных делают различные сокеты
     * и разделяют их портами.
    */
    QByteArray rcvData;
    rcvData = datagram.data();


    /*
     * Поскольку мы принимает дату в формате QDateTime необходимо десериализовать
     * Воспользуемся QDataStream, данный клас представляет потоковвый ввод вывод данных
     * и умеет работать с множеством стандартных типов данных
    */
    QDataStream stream(&rcvData, QIODevice::ReadOnly);
    QDateTime rcvTime;
    stream >> rcvTime;

    //После чтения данные необходимо передать в MainWindow
    emit sig_sendDataToGUI(rcvTime);

}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /* writeDatagram
     * Для отправки данных используется метод writeDatagram. Метод имеет несколько
     * перегрузок. Часто передают QBytearray, в таком случае первым параметром передается
     * ссылка QByteArray, вторым параметром IPадрес на который неоьбходимо отправить датаграмму
     * в формате QHostAddress и треьим порт на который необходимо отправить датаграмму.
    */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Слот осуществляет чтение датаграм из сокета
 */
void UDPworker::ReadPendingDatagrams( void )
{
    /* hasPendingDatagrams
     *  Структура функции обработчика приведена в официальной документации.
     *  По получению сигнала readyRead мы должны считать все доступные датаграммы
     *  из сокета. Чтение датаграмы осуществляется при помощи метода receiveDatagram
     *  который возвращает объект класса QNetworkDatagram.
     *  Также в этом цикле мы должны обработать датаграммы.
    */
    while(serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }

}
