#include <QApplication>
#include <QWidget>
#include <QPainter>
#include "mainwindow.h"




int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWidget w;
    w.show();
    return app.exec();
}

