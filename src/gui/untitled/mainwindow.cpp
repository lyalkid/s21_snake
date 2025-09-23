#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      tetris(new Tetris_Widget),
      snake(new Snake_Widget) {
  ui->setupUi(this);
  setFixedSize(300, 300);
  setWindowTitle("BRICK_GAME");

  central = new QWidget(this);
  layout = new QVBoxLayout(central);

  tetris_button = new QPushButton("tetris", central);
  snake_button = new QPushButton("snake", central);
  layout->addWidget(tetris_button);
  layout->addWidget(snake_button);

  setCentralWidget(central);
  connect(tetris_button, &QPushButton::clicked, this,
          &MainWindow::start_tetris);
  connect(snake_button, &QPushButton::clicked, this, &MainWindow::start_snake);

  connect(tetris, &Tetris_Widget::finished, this, &MainWindow::show);
  connect(snake, &Snake_Widget::finished_snake, this, &MainWindow::show);
}

MainWindow::~MainWindow() {
  // delete ui;
}

void MainWindow::start_tetris() {
  hide();
  tetris->show();
}
void MainWindow::start_snake() {
  hide();
  snake->show();
}
