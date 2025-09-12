#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timer(new QTimer(this)) {
    ui->setupUi(this);

    // запуск игрового цикла каждые 200 мс
    connect(timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer->start(200);

    // начальное состояние
    gameInfo = updateCurrentState();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        userInput(Left, false);
        break;
    case Qt::Key_Right:
        userInput(Right, false);
        break;
    case Qt::Key_Up:
        userInput(Up, false);
        break;
    case Qt::Key_Down:
        userInput(Down, false);
        break;
    case Qt::Key_Space:
        userInput(Action, false);
        break;
    case Qt::Key_P:
        userInput(Pause, false);
        break;
    case Qt::Key_Q:
        userInput(Terminate, false);
        close();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::gameLoop() {
    gameInfo = updateCurrentState();
    update(); // перерисовать окно
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int cellSize = 20;
    int offsetX = 50;
    int offsetY = 50;

    if (gameInfo.field) {
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (gameInfo.field[y][x] != 0) {
                    painter.fillRect(offsetX + x * cellSize,
                                     offsetY + y * cellSize,
                                     cellSize, cellSize,
                                     Qt::blue);
                    painter.drawRect(offsetX + x * cellSize,
                                     offsetY + y * cellSize,
                                     cellSize, cellSize);
                }
            }
        }
    }

    // инфо: очки
    painter.drawText(300, 100, QString("Score: %1").arg(gameInfo.score));
    painter.drawText(300, 120, QString("Level: %1").arg(gameInfo.level));
}
