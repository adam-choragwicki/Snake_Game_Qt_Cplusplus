#-------------------------------------------------
#
# Project created by QtCreator 2018-09-27T18:01:57
#
#-------------------------------------------------

QT       += core gui widgets

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = ../../Snake_Game_Qt_Cplusplus/executable_windows/Snake
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/game_window.cpp \
    src/snake.cpp \
    src/food.cpp \
    src/drawer.cpp

HEADERS += \
    inc/game_window.h \
    inc/snake.h \
    inc/food.h \
    inc/drawer.h

FORMS += \
    ui_forms/game_window.ui
