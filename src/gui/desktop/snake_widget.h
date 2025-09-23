#ifndef SNAKE_WIDGET_H
#define SNAKE_WIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/snake/model/Snake.h"
class Snake_Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Snake_Widget(QWidget *parent = nullptr);
  ~Snake_Widget() = default;
  void print_welcome(QPainter &p, Snake_state state);

 signals:
  void finished_snake();  //
 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void closeEvent(QCloseEvent *event) override;

 private:
  s21::Controller controller;
  QTimer *timer;

 private slots:
  void update_draw();
};

#endif  // SNAKE_WIDGET_H
