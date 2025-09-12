#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "../brick_game/tetris/game_api/game_api.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void MainWindow::paintEvent(QPaintEvent *) ;
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void gameLoop();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    GameInfo_t gameInfo;
};

#endif // MAINWINDOW_H
