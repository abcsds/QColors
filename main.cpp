#include <QtGui/QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;

    if (argc>0) {
        cerr << "Input given: Loading game... "<< endl;
        w.loadGame(argv[1]);
    }
    else w.newGame();
    w.show();

    return a.exec();
}
