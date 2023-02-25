cmake_minimum_required(VERSION 3.5)

project(PreDataBase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database.h
        database.cpp
        dbdata.h
        dbdata.cpp
        dbdata.ui
)

qt_add_executable(PreDataBase
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(PreDataBase PRIVATE Qt6::Widgets)

qt_finalize_executable(PreDataBase)
