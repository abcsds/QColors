//
//  colors.h
//  colors
//
//  Created by abcsds on 31/10/13.
//  Copyright (c) 2013 abcsds. All rights reserved.
//

#ifndef __colors__colors__
#define __colors__colors__

#include <iostream>
#include <QString>
#include <QChar>
#include <QVector>
#include <QColor>
#include <QMessageBox>
#include <QStack>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>
#define MAX 4294967296

using namespace std;
class colors {
private:
    QVector<char> grid;
    bool ready;
    int level;
public:
    colors();
    ~colors();

    void set();
    
    int readFromFile(QString s);
    int writeToFile(QString s);
    
    int scramble();
    void printGrid();
    bool isReady();
    bool isOver();
    void setLevel(int L);
    int getLevel();
    
    int rule(int i);
    int revert(int i);

    QVector<char> getGrid();
    
    void play();
    
};

#endif /* defined(__colors__colors__) */
