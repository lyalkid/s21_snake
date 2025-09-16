#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "../../brick_game/tetris/inc/tetris.h"
#ifdef __cplusplus
}
#endif
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <string.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui;
    // GameField* game_field;
    TetrisData_t* data;
    QTimer *timer;

private slots:
    void update_draw();

};
#endif // MAINWINDOW_H
