# Домашнее задание к занятию "Виджеты"

### Цель задания

В результате выполнения этого задания вы научитесь компоновать виджеты в контейнеры, изменять свойства виджетов из кода.

------

### Инструкция к заданию

1. Создать новый проект - приложение Qt Widget.
2. Добавить виджеты на форму главного окна
3. Изменить свойства виджетов в конструкторе класса MainWindow
4. Для изменение метода обработчика кнопки необходимо нажать в форме по ней ПКМ и выбрать "Перефти к слоту".
   В этот метод программа будт попадать при нажатии на кнопку

### Задание 1

1. Создать форму которая включает:
* 1 GroupBox с двумя RadioButton
* 1 Выпадающий список 
* 1 Кнопку
* 1 Прогресс бар
2. В конструкторе MainWindow необходимо:
* Задать имена всем двум RadioButton (которые отображаются на форме)
* Добавить несколько элементов в выпадающий список (не больше 10)
* Изменить надпись на кнопке
* Изменить тип кнопки на Toggle.
* установить начальные значения прогресс бар(минимум 0, максимум 10, текущее 0) 
3. По нажатию на кнопку прогресс бар должен увеличиваться на 10%. При увеличении более 100% прогресс бар должен сбрасываться на 0.

------

### Правила приема работы

1. Отправлена ссылка на репозиторий с кодом ДЗ

------

### Критерий зачета

* Соблюдено минимальное количество виджетов
* Отсутствуют нескомпанованные виджеты или компановки.
* Все именования, состав выподающего списка и тип кнопки определяется в конструкторе.
