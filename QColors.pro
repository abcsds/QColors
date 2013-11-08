#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T00:54:52
#
#-------------------------------------------------

QT       += core gui

TARGET = QColors
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    colors.cpp \
    table.cpp

HEADERS  += game.h \
    colors.h \
    table.h

FORMS    += game.ui

#QMAKE_CXXFLAGS += -std=c++0x
#QMAKE_CXXFLAGS = -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
#QMAKE_LFLAGS = -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7

RESOURCES += \
    res.qrc
