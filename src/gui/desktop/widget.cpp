#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget{parent} {
  setWindowTitle("BRICK_GAME");
  tetris_button = new QPushButton("tetris");
  layout = new QVBoxLayout(this);
  layout->addWidget(tetris_button);
}

Widget::~Widget() {}
