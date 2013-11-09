#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "colors.h"


namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    QColor getColor(char c);


    QString vector2Str(QVector<char> *colors);

    void setGrid();

    int checkStage();
    void solveStageOne();
    void solveStageTwo();
    void solveStageThree();
    void solveStageFour();
    void fourA();
    void fourB();
    void randomMove(bool one, bool two, bool three, bool four);
    QVector<int> findPair(char C1,char C2);

    void solve();

    void play();


protected:
    void paintEvent(QPaintEvent *e);
    
private slots:
    void on_Rule1button_clicked();

    void on_Rule2button_clicked();

    void on_Rule3button_clicked();

    void on_Rule4button_clicked();

    void on_RandomButton_clicked();

    void on_loopButton_clicked();

    void on_solveButton_clicked();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_levelSlider_sliderMoved(int position);

    void on_actionNewGame_triggered();

    void on_levelSlider_actionTriggered(int action);

private:
    Ui::Game *ui;
    colors g;
    QVector<char> grid;
    bool loop;
    QMessageBox help;
    QMessageBox about;
    bool solved;
    int stage;
    QTime time;
};

#endif // GAME_H
