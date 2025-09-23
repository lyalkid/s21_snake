#ifndef TETRIS_WIDGET_H
#define TETRIS_WIDGET_H

extern "C" {
#include "../../brick_game/tetris/inc/tetris.h"
#include "../../brick_game/utils/defines.h"
}

#include <QCloseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QWidget>

class Tetris_Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Tetris_Widget(QWidget *parent = nullptr);
  ~Tetris_Widget();

  void print_welcome(QPainter &p, Tetris_state_t state);
  void print_game(QPainter &p, int **field, int **next, int size);
  void print_info(QPainter &p, int level, int score, int high_score, int size);
  void print_next(QPainter &p, int type, int size);
  void paint_tetramino(QRectF cellRect, int value, QPainter &p, int size);

  QColor colorForType(int type) const;

 signals:
  void finished();  //
 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void closeEvent(QCloseEvent *event) override;

 private:
  TetrisData_t *data;
  QTimer *timer;

 private slots:
  void update_draw();
};

#endif  // TETRIS_WIDGET_H
