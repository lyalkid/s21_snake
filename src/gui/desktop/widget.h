#ifndef WIDGET_H
#define WIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  QPushButton *tetris_button;
  QVBoxLayout *layout;
};

#endif  // WIDGET_H
