#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../../brick_game/tetris/inc/tetris.h"
#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

#include <QApplication>
#include <QWidget>
#include <QPainter>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(600, 800);
        UserAction_t action = Start;
        userInput(action, true);
    }


protected:

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);

        int size_block = 20;
        // painter.setBrush(Qt::);
        // painter.drawRect(0, 0, WIDTH, HEIGHT); // квадрат
        for(int i= 0 ; i < HEIGHT;i++){
            for(int j = 0; j<  WIDTH; j++){
                painter.drawRect(size_block*j, size_block*i, size_block, size_block);
            }

        }

    }

};




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
