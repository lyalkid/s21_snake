#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// #ifdef __cplusplus
// extern "C" {
// #endif
// #include "../../brick_game/tetris/inc/tetris.h"
// #ifdef __cplusplus
// }
// #endif
// #include <string.h>

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "snake_widget.h"
#include "tetris_widget.h"
#include "ui_mainwindow.h"

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

 private:
  Ui::MainWindow *ui;
  Tetris_Widget *tetris;
  Snake_Widget *snake;
  QPushButton *tetris_button;
  QPushButton *snake_button;
  QVBoxLayout *layout;
  QWidget *central;

 private slots:
  void start_tetris();
  void start_snake();
};
#endif  // MAINWINDOW_H
