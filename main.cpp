#include <QtGui/QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;
//    for(int i = 0; i < a.arguments().size(); i++) {
//        cerr << a.arguments().at(i).toStdString() << endl;
//    }
    if (argc>0) {
        cerr << argv[1] << endl;
        cerr << "Loading game... "<< endl;
        w.loadGame(argv[1]);
    }
    else w.newGame();
    w.show();

    return a.exec();
}
