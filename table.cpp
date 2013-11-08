#include "table.h"

table::table()
{
}

void table::setFile(QFile *file)
{
    this->file = file;
}

void table::createTable()
{
    moves = openFile();
    moves = toBaseTen(moves);
    //cerr << "moves: " << moves << endl;
    file->open(QIODevice::Append|QIODevice::Text);
    if(file->isOpen()){
        t.start();
        explore();
        qDebug("Time elapsed until finished: %d min", t.elapsed()/60000);

        // Save time of progress
        QFile fi("/Users/abcsds/Desktop/times.txt");
        fi.open(QIODevice::Append|QIODevice::Text);
        QTextStream out(&fi);
        out << "Time elapsed until finished: " << t.elapsed()/60000 <<  "min." << endl;
        file->flush();
        file->close();
        fi.close();

    } else cerr << "Error openning file"<< endl;
    file->close();
    QMessageBox msgBox;
     msgBox.setText("Hash Table Finished");
     msgBox.exec();
}

void table::explore()
{
    unsigned int n;
    QString s;
    for(int i = moves; i < MAX;i++) {
        game.set();
        n = toBaseFour(i);

        cerr << "Number: " << n << endl;
        move(n);
        QVector<char> c = game.getGrid();
        //cerr << "Size of grid: " << c.size() << endl;
        QString str = vector2Str(&c);
        //if(!isInTable(str))
       // {
            writeToTable(str,QString::number(n));
       // }
    }
}

bool table::isInTable(QString s)
{
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream io(file);
    QString str;
    str = io.readLine();
    while(!str.isNull()) {
        //cerr << str.toStdString() << endl;
        if(str.indexOf(s)!=-1) {
            file->close();
            return true;
        }
        str = io.readLine();
    }
    return false;
}

void table::writeToTable(QString colors, QString numbers)
{
    //file->open(QIODevice::Append|QIODevice::Text);
    QTextStream out(file);
    out << colors << ":" << numbers << endl;
    file->flush();
    cerr << "writen: " << colors.toStdString() << ":" << numbers.toStdString() << endl;
}

QString table::vector2Str(QVector<char> *colors)
{
    QString str;
    for(int i = 0; i<colors->size();i++) {
        str.append(colors->at(i));
    }
    return str;
}

unsigned int table::openFile()
{
    if(file->exists()) {
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream io(file);
        QString str;
        QString lastStr = 0;
        str = io.readLine();
        while(!str.isNull()) {
            lastStr = str;
            str = io.readLine();
        }
        str = lastStr;
        //cerr << str.toStdString() << endl;

        QStringList list = str.split(':');
        str = list[1];
        cerr << "last number found: " << str.toStdString() << endl;
        file->close();
        return str.toInt();
    }
    else  {
        return 0;
    }
}

unsigned int table::toBaseTen(unsigned int n)
{
    QString s = QString::number(n);
    int size = s.size();
    int num = 0;
    for(int i = 0; i<size;i++) {
        int power = qPow(4,i);
        int number = s[size-i-1].digitValue();
        num += number*power;
    }
    return num;
}

unsigned int table::toBaseFour(unsigned int n)
{
    QStack<int> r;
    QString s;
    while(n) {
        r.push(n%4);
        n = n/4;
        if(n<4) break;
    }
    while(!r.isEmpty()) {
        s.append(QString::number(r.top()));
        r.pop();
    }

    s.append(n);

    cerr << "to base four: --" << s.toStdString() << "--" << endl;
    unsigned int num = (unsigned int)s.toInt();
    cerr << "to base four: " << num << endl;
    return num;
}

void table::move(unsigned int moves)
{
    unsigned int n = moves;
    if(n == 0) game.rule(1);
    else {
        while(n) {
            //cerr << "In game, moving: " << n%10+1 << endl;
            game.rule(n%10+1);
            n = n/10;
        }
    }
}

QStack<int> table::findInTable(QVector<char> vect)
{
    QString s = vector2Str(&vect);
    file->close();
    file->open(QIODevice::ReadOnly|QIODevice::Text);
    if(file->isOpen()) {

        QTextStream io(file);
        s = io.readLine();
        cerr << "Moves from file: " << s.toStdString() << endl;
        while(!s.isNull()) {
            if(s.indexOf(s)!=-1) break;
            s = io.readLine();
            cerr << "Moves from file: " << s.toStdString() << endl;
        }
        QStringList list = s.split(':');
        s = list[1];
        cerr << "Selected move from file: " << s.toStdString() << endl;
        QStack<int> stack;
        for(int i = 0; i< s.size(); i++) {
            stack.push(s[i].digitValue()+1);
        }
        file->close();
        return stack;
    }
    QStack<int> stack;
    return stack;
}




