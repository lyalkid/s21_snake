#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H


#ifdef __cplusplus
extern "C" {
#endif
#include "brick_game/tetris/inc/tetris.h"
#ifdef __cplusplus
}
#endif

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>


class T_widget: public QWidget{
    Q_OBJECT

public:
    T_widget (QWidget* parrent = nullptr);
    ~T_widget();

protected:
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    TetrisData_t* data;
    QTimer *timer;

private slots:
    void update_draw();
};




#endif // TETRISWIDGET_H
