#include "mainwindow.h"
#include "../../brick_game/tetris/inc/tetris.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
