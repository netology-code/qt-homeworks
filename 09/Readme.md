# Домашнее задание к занятию "Работа с сетью. UDP клиент"

### Цель задания

В результате выполнения этого задания вы научитесь создавать UDP сокеты, принимать и отправлять датаграммы, а также работать с несколькими сокетами в одном приложении.

------

### Инструкция к заданию

1. Скачать проект с прекодом.
2. Добавить в CMakeList.txt модуль для работы с сетью.
4. Добавить на главную форму виджет для ввода текста и кнопку "Отправить Датаграмму"
5. Изменить существующие или добавить новые методы, необходимые для выполнения задания.

------

### Задание 1. 

Доработать представленное приложение, чтобы появился функционал отправки и приема пользовательских датаграмм.

1. В текущее приложение добавить:
 * виджет для ввода текста;
 * кнопку "Отправить датаграмму".
2. При нажатии на кнопку "Отправить датаграмму" приложение должно отправить введенный пользователем текст при помощи объекта класса QUdpSocket на адрес 127.0.0.1 (localhost)
3. Приложение должно принять эту датаграмму и отобразить в виджете "Принятые данные" сообщение вида: "Принято сообщение от ***адрес отправителя***, 
   размер сообщения(байт) ***Х***
   * Х - размер введенного в виджет текста
   * Адрес отправителя - адрес с которого была осуществлена отправка датаграммы

------

### Правила приема работы

1. Отправлена ссылка на репозиторий с кодом ДЗ

------

### Критерий зачета

* Выполняются все требования из задания.
* Сообщения отправляются и принимаются при помощи экземпляров классов QUdpSocket.
* Вся работа классов QUdpSocket реализована внутри класса UDPworker.
* Не нарушен предыдущий функционал приложения.
