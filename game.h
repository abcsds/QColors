#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "colors.h"
#include "table.h"


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

    void solve();
    QStack<int> findInTable(QVector<char> *grid);

    void createTable();
    void explore(colors *g, QStack<int> *moves, int level);
    bool isInTable(QString s);
    void writeToTable(QString colors, QString numbers);
    QString vector2Str(QVector<char> *colors);
    QString stack2Str(QStack<int> *numbers);




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
    bool loop;
    QMessageBox help;
    QMessageBox about;
    bool solved;
    QFile file;
    table hash;
};

#endif // GAME_H
