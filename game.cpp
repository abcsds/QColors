#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    loop = true;
    solved = false;
    g.setLevel(10);
    help.setText("QColors Game: Spin the squares CCW arround a pivot to get the starting combination.");
    about.setText("Author: Alberto Barradas, Universidad de Guanajuato 2013");
    //play();
    randomPlay();
}

Game::~Game()
{
    delete ui;
}
void Game::paintEvent(QPaintEvent *e) {
    if(loop) {
    QVector<char> grid = g.getGrid();
    QPalette p;

    p = ui->textEdit_1->palette();
    p.setColor(QPalette::Base, getColor(grid[0]));
    ui->textEdit_1->setPalette(p);

    p = ui->textEdit_2->palette();
    p.setColor(QPalette::Base, getColor(grid[1]));
    ui->textEdit_2->setPalette(p);

    p = ui->textEdit_3->palette();
    p.setColor(QPalette::Base, getColor(grid[2]));
    ui->textEdit_3->setPalette(p);

    p = ui->textEdit_4->palette();
    p.setColor(QPalette::Base, getColor(grid[3]));
    ui->textEdit_4->setPalette(p);

    p = ui->textEdit_5->palette();
    p.setColor(QPalette::Base, getColor(grid[4]));
    ui->textEdit_5->setPalette(p);

    p = ui->textEdit_6->palette();
    p.setColor(QPalette::Base, getColor(grid[5]));
    ui->textEdit_6->setPalette(p);

    p = ui->textEdit_7->palette();
    p.setColor(QPalette::Base, getColor(grid[6]));
    ui->textEdit_7->setPalette(p);

    p = ui->textEdit_8->palette();
    p.setColor(QPalette::Base, getColor(grid[7]));
    ui->textEdit_8->setPalette(p);

    p = ui->textEdit_9->palette();
    p.setColor(QPalette::Base, getColor(grid[8]));
    ui->textEdit_9->setPalette(p);

    p = ui->textEdit_10->palette();
    p.setColor(QPalette::Base, getColor(grid[9]));
    ui->textEdit_10->setPalette(p);

    p = ui->textEdit_11->palette();
    p.setColor(QPalette::Base, getColor(grid[10]));
    ui->textEdit_11->setPalette(p);

    p = ui->textEdit_12->palette();
    p.setColor(QPalette::Base, getColor(grid[11]));
    ui->textEdit_12->setPalette(p);

    p = ui->textEdit_13->palette();
    p.setColor(QPalette::Base, getColor(grid[12]));
    ui->textEdit_13->setPalette(p);

    p = ui->textEdit_14->palette();
    p.setColor(QPalette::Base, getColor(grid[13]));
    ui->textEdit_14->setPalette(p);

    p = ui->textEdit_15->palette();
    p.setColor(QPalette::Base, getColor(grid[14]));
    ui->textEdit_15->setPalette(p);

    p = ui->textEdit_16->palette();
    p.setColor(QPalette::Base, getColor(grid[15]));
    ui->textEdit_16->setPalette(p);

    if(solved){
        QMessageBox msgBox;
         msgBox.setText("Congratulations, you have finished the game!");
         msgBox.exec();
         solved = false;
    }
}
    this->update();
    //e->accept();
}
QColor Game::getColor(char c) {
    switch(c) {
    case 'R':
        return Qt::red;
        break;
    case 'B':
        return Qt::blue;
        break;
    case 'Y':
        return Qt::yellow;
        break;
    case 'G':
        return Qt::green;
        break;
    default:
        return Qt::black;
    }
}

void Game::on_Rule1button_clicked()
{
    g.rule(1);
    solved = g.isOver();
}

void Game::on_Rule2button_clicked()
{
    g.rule(2);
    solved = g.isOver();
}

void Game::on_Rule3button_clicked()
{
    g.rule(3);
    solved = g.isOver();
}

void Game::on_Rule4button_clicked()
{
    g.rule(4);
    solved = g.isOver();
}

void Game::on_actionNewGame_triggered()
{
    g.set();
}

void Game::on_actionSave_triggered()
{
    QString s = QFileDialog::getSaveFileName(this, "Save");
    cerr << s.toStdString() << endl;
    if(!s.isEmpty()) {
        g.writeToFile(s);
    }
}

void Game::on_actionOpen_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, "Open");
    cerr << s.toStdString() << endl;
    if(!s.isEmpty()) {
        g.readFromFile(s);
    }
}

void Game::on_RandomButton_clicked()
{
    g.scramble();
    solved = false;
}

void Game::on_loopButton_clicked()
{
    loop = !loop;
    if(loop) ui->loopButton->setText("Loop: ON");
    else ui->loopButton->setText("Loop: OFF");
}

void Game::on_levelSlider_sliderMoved(int position)
{
    g.setLevel(position);
    QString l = "Level ";
    l.append(QString::number(position));
    ui->levelLabel->setText(l);
}

void Game::on_levelSlider_actionTriggered(int action)
{
    int position = ui->levelSlider->value();
    g.setLevel(position);
    QString l = "Level ";
    l.append(QString::number(position));
    ui->levelLabel->setText(l);
}

void Game::on_solveButton_clicked()
{
    solve();
}

void Game::on_actionHelp_triggered()
{
    help.exec();
}

void Game::on_actionAbout_triggered()
{
    about.exec();
}

void Game::setGrid()
{
    grid = g.getGrid();
}

int Game::checkStage()
{
    int n=0;
    setGrid();
    if(grid[0]!='R') return 1;
    if( grid[0]=='R') n=2;
    if( n==2 && grid[1]=='R' && grid[2]=='B' && grid[3]=='B') n = 3;
    if( n==3 && (grid[4]=='R'&&grid[5]=='R'&&grid[6]=='B' && grid[7]=='B') ) n = 4;
    return n;
}

void Game::solveStageOne()
{
    setGrid();
    while(grid[0]!='R')
    {
        randomMove(1,1,1,1);
        setGrid();
    }
}

void Game::solveStageTwo()
{
    setGrid();
    while(grid[8]!='B'|| grid[12]!='B')
    {
        randomMove(0,1,1,1);
        setGrid();
    }
    //cerr << "(8,12) : (" << grid[8] << "," << grid[12] << ")"<< endl;
    //g.printGrid();
    while(grid[14]!='R') {
        randomMove(0,1,0,1);
        setGrid();
    }
    //g.printGrid();
    g.revert(3);
    g.rule(4);
    g.rule(3);
    g.rule(2);
    g.rule(2);
    setGrid();

}

void Game::solveStageThree()
{
    do {
        setGrid();
        while(grid[11]!='R'|| grid[15]!='R' || grid[12]!='B')
        {
            randomMove(0,0,1,1);
            setGrid();
            if(time.elapsed()>25) solveStageTwo();
        }
        g.rule(4);
        g.rule(3);
        int count = 0;
        while(grid[7]!='B')
        {
            randomMove(0,0,1,1);
            setGrid();
            count++;
            if (count > 10) break;
        }
        //g.rule(3);
    } while (grid[4]!='R'|| grid[5]!='R' || grid[6]!='B' || grid[7]!='B');
}

void Game::solveStageFour()
{
    int n;
    while(!g.isOver()) {
        n = rand()%2;
        if(n) fourA();
        else fourB();
    }
}

void Game::fourA()
{
    g.revert(1);
    g.rule(2);
    g.rule(1);
    g.revert(4);
    g.revert(3);
    g.rule(4);
    g.rule(4);
    g.revert(3);
    g.rule(4);
    g.rule(3);
    g.rule(4);
    g.rule(3);
}

void Game::fourB()
{
    g.rule(2);
    g.revert(1);
    g.revert(2);
    g.rule(3);
    g.rule(4);
    g.rule(3);
    g.rule(3);
    g.rule(4);
    g.revert(3);
    g.revert(4);
    g.rule(3);
    g.revert(4);
}
void Game::randomMove(bool one, bool two, bool three, bool four)
{
    int i = rand()%4;
    switch(i) {
    case 0:
        if(one) g.rule(1);
        break;
    case 1:
        if(two) g.rule(2);
        break;
    case 2:
        if(three) g.rule(3);
        break;
    case 3:
        if(four) g.rule(4);
        break;
    }
    setGrid();
}

QVector<int> Game::findPair(char C1, char C2)
{
    QVector<int> v;
    setGrid();
    for(int i = 0; i < 4; i++) {
        if(grid[i]==C1 && grid[i+1]==C2) {
            v.append(i);
            v.append(i+1);

        }
        if(grid[i+1]==C1 && grid[i]==C2) {
            v.append(i+1);
            v.append(i);

        }
    }
    for(int i = 4; i < 8; i++) {
        if(grid[i]==C1 && grid[i+1]==C2) {
            v.append(i);
            v.append(i+1);

        }
        if(grid[i+1]==C1 && grid[i]==C2) {
            v.append(i+1);
            v.append(i);

        }
    }
    for(int i = 8; i < 12; i++) {
        if(grid[i]==C1 && grid[i+1]==C2) {
            v.append(i);
            v.append(i+1);

        }
        if(grid[i+1]==C1 && grid[i]==C2) {
            v.append(i+1);
            v.append(i);

        }
    }
    for(int i = 12; i < 16; i++) {
        if(grid[i]==C1 && grid[i+1]==C2) {
            v.append(i);
            v.append(i+1);

        }
        if(grid[i+1]==C1 && grid[i]==C2) {
            v.append(i+1);
            v.append(i);

        }
    }
    for(int i = 0; i < 16 ; i++) {
        if(grid[i]==C1 && grid[i+4]==C2) {
            v.append(i);
            v.append(i+4);

        }
        if(grid[i+4]==C1 && grid[i]==C2) {
            v.append(i+4);
            v.append(i);

        }
    }
    return v;
}

void Game::solve() {
    time.start();
    stage = checkStage();
    switch(stage) {
    case 1:
        solveStageOne();
    case 2:
        solveStageTwo();
    case 3:
        solveStageThree();
    case 4:
        solveStageFour();
    }

}

void Game::play()
{
    QFile f("/Users/abcsds/Documents/Programs/QT/QColors/times.txt");
    f.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&f);
    int n = 1000;
    g.set();
    g.setLevel(99);
    out << "Times for solving " << n << " puzles scrablead a 99 times each:" << endl;
    QTime t, total;
    total.start();
    for(int i = 0; i<n; i++) {
        t.start();
        g.scramble();
        solve();
        out << "Puzzle " << i << ": " << t.elapsed() << " ms." << endl;
        t.restart();
    }
    out << "Total time: " << total.elapsed() << " ms." << endl;

}

void Game::randomPlay()
{
    QFile f("/Users/abcsds/Documents/Programs/QT/QColors/timesRandom.txt");
    f.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&f);
    QTime total;
    g.setLevel(99);
    g.set();
    g.scramble();
    out << "Total time to finish with random moves: " << endl;
    //out << "Moves to do for each solving: " << endl;
    for(int i = 0; i<1000;i++) {
        //int count  = 0;
        total.start();
        while(!g.isOver()) {
            randomMove(1,1,1,1);
            //count ++;
        }
        out << total.elapsed() << " ms" << endl;
        //out << count << " moves" << endl;
        total.restart();
        g.scramble();
    }
}





