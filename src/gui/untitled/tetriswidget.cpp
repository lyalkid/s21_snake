#include "tetriswidget.h"


T_widget::T_widget(QWidget* parent): QWidget(parent){
    setFixedSize(600, 800);
    setWindowTitle("Tetris");
    timer = new QTimer;
     data = get_data();
    connect(timer, &QTimer::timeout, this, &T_widget::update_draw);
    timer->start(50);
}
T_widget::~T_widget(){
    delete timer;

}


void T_widget::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e)
    QPainter p(this);
    p.drawRect(0, 0, 300, 600);
    GameInfo_t inf = updateCurrentState();
    ;
    for (int i{}; i < 20; ++i) {
        for (int j{}; j < 10; ++j) {
            if (inf.field[i][j]) {
                p.setBrush(Qt::black);
            } else {
                p.setBrush(Qt::white);
            }
            p.drawRect(30 * j, 30 * i, 30, 30);
        }
    }

}

// using namespace :Qt;
void T_widget::keyPressEvent(QKeyEvent *e) {
    UserAction_t action;
    switch (e->key()) {
    case Qt::Key_Up:
        action = Up;
        break;
    case Qt::Key_Down:
        action = Down;
        break;
    case Qt::Key_Left:
        action = Left;
        break;
    case Qt::Key_Right:
        action = Right;
        break;
    case 'p':
        action = Pause;
        break;
    case 'n':
        action = Start;
        break;
    case 'q':
        action = Terminate;

        break;
    case 'f':
        action = Action;
        break;
    default:
        action = (UserAction_t)NONE_ACTION;
        break;

    }

    userInput(action, false);
    update_draw();
    if(action == Terminate){
        QWidget::close();
    }
}
void T_widget::update_draw(){
    repaint();
}
