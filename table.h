#ifndef TABLE_H
#define TABLE_H
#include "colors.h"

class table
{
public:
    table();
    void setFile(QFile *file);
    void createTable();
    void explore();
    bool isInTable(QString s);
    void writeToTable(QString colors, QString numbers);
    QString vector2Str(QVector<char> *colors);
    QString stack2Str(QStack<int> *numbers);
    unsigned int openFile();
    unsigned int toBaseTen(unsigned int n);
    unsigned int toBaseFour(unsigned int n);
    unsigned int increment(unsigned int moves);
    void move(unsigned int moves);

    QStack<int> findInTable(QVector<char> vect);

private:
    QFile *file;
    QTime t;
    unsigned int moves;
    colors game;
};

#endif // TABLE_H
