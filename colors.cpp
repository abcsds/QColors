//
//  colors.cpp
//  colors
//
//  Created by abcsds on 31/10/13.
//  Copyright (c) 2013 abcsds. All rights reserved.
//

#include "colors.h"
colors::colors() {
    grid << 'R';
    grid << 'R';
    grid << 'B';
    grid << 'B';
    grid << 'R';
    grid << 'R';
    grid << 'B';
    grid << 'B';
    grid << 'Y';
    grid << 'Y';
    grid << 'G';
    grid << 'G';
    grid << 'Y';
    grid << 'Y';
    grid << 'G';
    grid << 'G';
    ready = true;
}
colors::~colors() {
    
}

void colors::set() {
    grid.erase(grid.begin(),grid.end());
    grid << 'R';
    grid << 'R';
    grid << 'B';
    grid << 'B';
    grid << 'R';
    grid << 'R';
    grid << 'B';
    grid << 'B';
    grid << 'Y';
    grid << 'Y';
    grid << 'G';
    grid << 'G';
    grid << 'Y';
    grid << 'Y';
    grid << 'G';
    grid << 'G';
    ready = true;
}

int colors::readFromFile(QString s) {
    QString line;
    QFile file(s);
    int counter=0;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        int found;
        int count = 0;

        QChar c;
        QTextStream in(&file);
        QString line = in.readLine(10);
        while ( !line.isNull() )
        {
            found = line.toStdString().find_first_of("RBYG");
            while(found < line.size())
            {
                c = line[found];
                if (counter < 4) {
                    char ch = c.toAscii();
                    grid.push_back(ch);
                    grid[count] = ch;
                    count++;
                }
                else {
                    cerr << "File has doesn't have the specified format: ending file reading." << endl;
                    return 0;
                }

                counter++;
                found=line.toStdString().find_first_of("RBYG",found+1);
                if(found==-1) break;
            }
            counter = 0;
            line = in.readLine();
        }
        file.close();
        return 1;
    }
    
    else cerr << "Unable to open file" << endl;
    
    return 0;
}
int colors::writeToFile(QString s) {

    QFile file(s);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    if(file.isOpen()&&ready) {
        int c = 0;
        QTextStream out(&file);
        for (int i = 0; i<16; i++) {
            c++;
            out << grid[i] << " ";
            if (c%4==0) {
                out << endl;
            }
        }
        file.close();
        return 1;
    }

    else return 0;
}

int colors::scramble() {
    if (ready) {
        srand((unsigned int)time(NULL));
        
        int it = level;
        cerr << "Scrambling " << it << "times." << endl;
        int r = random()%4 +1;
        
        for (int i = 0; i<it; i++) {
            r = random()%4 +1;
            if ( r>0 && r<5 ) rule(r);
            else cerr << "Couldn't apply random rule" << endl;
        }
        return 1;
    }
    return 0;
}

void colors::printGrid() {
    int c = 0;
    for (int i = 0; i<16; i++) {
        c++;
        cout<< grid[i] << " " ;
        if (c%4==0) {
            cout << endl;
        }
    }
}
bool colors::isReady() {
    return ready;
}
bool colors::isOver() {
    int c =0;
    if (grid[0] == 'R' && grid[1] == 'R' && grid[4] == 'R' && grid[5] == 'R') c++;
    if (grid[2] == 'B' && grid[3] == 'B' && grid[6] == 'B' && grid[7] == 'B') c++;
    if (grid[8] == 'Y' && grid[9] == 'Y' && grid[12] == 'Y' && grid[13] == 'Y') c++;
    if (grid[10] == 'G' && grid[11] == 'G' && grid[14] == 'G' && grid[15] == 'G') c++;
    return c==4?true:false;
    
}

void colors::setLevel(int L) {
    level = L;
}

int colors::getLevel() {
    return level;
}

int colors::rule(int i) {
    int temp;
    if (!isReady()) {
        return 0;
    }
    if (i>0&&i<5) {
        switch (i) {
            case 1:
                temp = grid[0];
                grid[0] = grid[8];
                grid[8] = grid[10];
                grid[10] = grid[2];
                grid[2] = temp;
                temp = grid[1];
                grid[1] = grid[4];
                grid[4] = grid[9];
                grid[9] = grid[6];
                grid[6] = temp;
                break;
            case 2:
                temp = grid[1];
                grid[1] = grid[9];
                grid[9] = grid[11];
                grid[11] = grid[3];
                grid[3] = temp;
                temp = grid[2];
                grid[2] = grid[5];
                grid[5] = grid[10];
                grid[10] = grid[7];
                grid[7] = temp;
                break;
            case 3:
                temp = grid[4];
                grid[4] = grid[12];
                grid[12] = grid[14];
                grid[14] = grid[6];
                grid[6] = temp;
                temp = grid[5];
                grid[5] = grid[8];
                grid[8] = grid[13];
                grid[13] = grid[10];
                grid[10] = temp;
                break;
            case 4:
                temp = grid[5];
                grid[5] = grid[13];
                grid[13] = grid[15];
                grid[15] = grid[7];
                grid[7] = temp;
                temp = grid[6];
                grid[6] = grid[9];
                grid[9] = grid[14];
                grid[14] = grid[11];
                grid[11] = temp;
                break;
                
            default:
                cerr << "Couldn't apply rule" <<endl;
                break;
        }
    }
    return 1;
}

int colors::revert(int i) {
        rule(i);
        rule(i);
        rule(i);
        return 1;
}

//void colors::play() {
//    int opc;
//    QString o;
//    locale loc;
//    cout << "Game being scrambled..." << endl;
//    scramble();
//    printGrid();
//    cout <<  endl;
//    while (!isOver()) {
//        cout << endl;
//        cout << "Choose a sector to rotate clockwise: " << endl;
//        cout << " 1 2 " << endl;
//        cout << " 3 4 " << endl;
//        cin >> o;
//        if (isdigit(o[0])) {
//            opc = stoi(o);
//            if (opc > 0 && opc < 5) rule(opc);
//            else cout << "Wrong option" << endl;
//        }
//        else cout << "Wrong option" << endl;
//        cout << endl;
//        printGrid();
//    }
//    cout << "Congratulations! You've finished the puzzle." << endl;
//}

QVector<char> colors::getGrid() {
    return grid;
}
