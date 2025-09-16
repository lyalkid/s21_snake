#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(600, 800);
    setWindowTitle("Tetris");
    timer = new QTimer;
    // data = get_data();
    connect(timer, &QTimer::timeout, this, &MainWindow::update_draw);
    timer->start(1);
    // game_field = new GameField();
    setFixedSize(500, 500);
    data = get_data();
    // on_tetris();
}

MainWindow::~MainWindow()
{
    delete ui;
    // delete game_field;
}

void MainWindow::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e)
    QPainter p(this);
    p.drawRect(0, 0, 300, 600);

    GameInfo_t inf = updateCurrentState();
    int** field = inf.field;
    int** next = get_data()->current_tetraMino.tmp_current_figure_on_field;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int res = field[i][j] + next[i][j];
            if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    ;
    int size = 20;
    for (int i{}; i < 20; ++i) {
        for (int j{}; j < 10; ++j) {
            int res = field[i][j] + next[i][j];
            if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
                p.setBrush(Qt::black);
            } else {
                p.setBrush(Qt::white);
            }
            p.drawRect(size * j, size * i, size, size);
        }
    }
    std::string s =  (char*)actionToString(get_data()->current_action);
      p.drawText(305, 205, s.data());
    std::string w = (char*)stateToString(get_data()->current_state);
      p.drawText(325, 225, w.data());
}

// using namespace :Qt;
void MainWindow::keyPressEvent(QKeyEvent *e) {
    UserAction_t action;
    switch (e->key()) {
    case Qt::Key_P:
        action = Pause;
        break;
    case Qt::Key_N:
        action = Start;
        break;
    case Qt::Key_Q:
        action = Terminate;
        break;
    case Qt::Key_A:
        action = Left;
        break;
    case Qt::Key_D:
        action = Right;
        break;
    case Qt::Key_W:
        action = Up;
        break;
    case Qt::Key_S:
        action = Down;
        break;
    case Qt::Key_F:
        action = Action;
        break;
    default:
        // action = (UserAction_t)NONE_ACTION;
        break;

    }
    get_data()->current_action = action;
    userInput(action, false);
    countTime(&get_data()->shift_timer);
    update_draw();
     if(action == Terminate){
        QWidget::close();
    }
}
void MainWindow::update_draw(){
    userInput((UserAction_t)NONE_ACTION, true);
    repaint();

}


