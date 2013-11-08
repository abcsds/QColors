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

    file.setFileName("/Users/abcsds/Desktop/table.txt");
    hash.setFile(&file);
    hash.createTable();
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


void Game::solve() {
    QVector<char> vect = g.getGrid();
    if (!hash.isInTable(hash.vector2Str(&vect))) {
        QMessageBox msgBox;
         msgBox.setText("Couldn't find a solution to this game.");
         msgBox.exec();
    } else {
        QStack<int> moves = hash.findInTable(vect);

        cerr << "moves:";
        for(int i = 0; i<moves.size();i++) {
            cerr << moves[i];
        }
        cerr << endl;

        for(int i = 0; i<moves.size();i++) {
            cerr << "Reverting rule: " << moves[i] << endl;
            g.revert(i);
        }
        // TADA! solved :)
    }

}

