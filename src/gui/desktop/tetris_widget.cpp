#include "tetris_widget.h"

Tetris_Widget::Tetris_Widget(QWidget* parent) : QWidget{parent} {
  setFixedSize(350, 400);
  setWindowTitle("TETRIS");
  timer = new QTimer;

  connect(timer, &QTimer::timeout, this, &Tetris_Widget::update_draw);
  timer->start(1);

  data = get_data();
}
Tetris_Widget::~Tetris_Widget() { delete timer; }

void Tetris_Widget::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e)
  QPainter p(this);
  GameInfo_t inf = updateCurrentState();
  int** field = inf.field;
  int** next = get_data()->current_tetraMino.tmp_current_figure_on_field;
  int size = 20;

  if (data->current_state == STATE_INITIALIZE ||
      data->current_state == STATE_PAUSE ||
      data->current_state == STATE_GAME_OVER) {
    print_welcome(p, data->current_state);
  } else {
    print_game(p, field, next, size);
    print_next(p, data->current_tetraMino.next_type, size);
    print_info(p, inf.level, inf.score, inf.high_score, size);
  }
}
//
void Tetris_Widget::print_welcome(QPainter& p, Tetris_state_t state) {
  p.save();
  p.setRenderHint(QPainter::Antialiasing);
  QRect r = rect();

  // фон (полупрозрачный затемняющий)
  p.fillRect(r, QColor(0, 0, 0, 160));

  // заголовок
  QFont titleF("Arial", 48, QFont::Bold);
  p.setFont(titleF);
  p.setPen(Qt::white);
  QRect titleRect = r.adjusted(20, r.height() / 6, -20, -r.height() / 2);

  // инструкции
  QFont subF("Arial", 14);
  p.setFont(subF);
  QRect subRect = r.adjusted(20, r.height() / 2, -20, -20);
  if (state == STATE_INITIALIZE) {
    p.drawText(titleRect, Qt::AlignCenter, "TETRIS");
    p.drawText(subRect, Qt::AlignCenter,
               "Нажмите n чтобы начать\nWASD — перемещение, f — поворот");
  } else if (state == STATE_GAME_OVER) {
    p.drawText(titleRect, Qt::AlignCenter, "GAME_OVER");
    p.drawText(
        subRect, Qt::AlignCenter,
        "Нажмите n чтобы начать сначала\nWASD — перемещение, f — поворот");
  } else if (state == STATE_PAUSE) {
    p.drawText(titleRect, Qt::AlignCenter, "PAUSE");
    p.drawText(subRect, Qt::AlignCenter,
               "Нажмите p чтобы начать\nWASD — перемещение, f — поворот");
  }
  p.restore();
}
//
// void Tetris_Widget::print_game(QPainter& p, int** field, int** next, int size) {
//   // for (int i{}; i < HEIGHT; ++i) {
//   //     for (int j{}; j < WIDTH; ++j) {
//   //         int res = field[i][j] + next[i][j];
//   //         if (!((res != 0 && field[i][j] == 0) || field[i][j] != 0)) {
//   //             p.setBrush(Qt::black);
//   //         } else if (res == 1) {
//   //             p.setBrush(Qt::red);
//   //         } else if (res == 2) {
//   //             p.setBrush(Qt::cyan);
//   //         } else if (res == 3) {
//   //             p.setBrush(Qt::blue);
//   //         } else if (res == 4) {
//   //             p.setBrush(Qt::yellow);
//   //         } else if (res == 5) {
//   //             p.setBrush(Qt::white);
//   //         } else if (res == 6) {
//   //             p.setBrush(Qt::green);
//   //         } else if (res == 7) {
//   //             p.setBrush(Qt::magenta);
//   //         }
//   //         p.drawRect(size * j, size * i, size, size);
//   //     }
//   // }
//   p.save();
//   p.setRenderHint(QPainter::Antialiasing);
//   p.setRenderHint(QPainter::SmoothPixmapTransform);
//   // По умолчанию не рисуем контур при заполнении, потом рисуем контур отдельно
//   p.setPen(Qt::NoPen);
//
//   for (int i = 0; i < HEIGHT; ++i) {
//     for (int j = 0; j < WIDTH; ++j) {
//       // Правильное наложение: если есть в поле — берем его, иначе берем next
//       int value = (field[i][j] != 0) ? field[i][j] : next[i][j];
//
//       QRect cellRect(qreal(size * j), qreal(size * i), qreal(size),
//                      qreal(size));
//       paint_tetramino(cellRect, value, p, size);
//     }
//   }
//
//   p.restore();
// }
//
// void Tetris_Widget::paint_tetramino(QRectF cellRect, int value, QPainter& p,
//                                     int size) {
//   const qreal radius = size * 0.18;
//   const qreal borderWidth = qMax(1.0, size * 0.06);
//   if (value == 0) {
//     // фон клетки (чтобы было видно сетку) — чуть темнее
//     QLinearGradient bgGrad(cellRect.topLeft(), cellRect.bottomRight());
//     bgGrad.setColorAt(0.0, QColor(15, 15, 20));
//     bgGrad.setColorAt(1.0, QColor(8, 8, 12));
//     p.setBrush(bgGrad);
//     p.drawRect(cellRect);
//     return;
//   }
//
//   QColor base = colorForType(value + 1);
//
//   // тень под блоком (смещение и полупрозрачность)
//   QRectF shadowRect = cellRect.translated(size * 0.06, size * 0.06);
//   p.setBrush(QColor(0, 0, 0, 90));
//   p.setPen(Qt::NoPen);
//   p.drawRoundedRect(shadowRect, radius, radius);
//
//   // основной градиент блока — светлее сверху и темнее снизу
//   QLinearGradient grad(cellRect.topLeft(), cellRect.bottomRight());
//   grad.setColorAt(0.0, base.lighter(135));  // верх — светлее
//   grad.setColorAt(0.6, base);
//   grad.setColorAt(1.0, base.darker(140));  // низ — темнее
//   p.setBrush(grad);
//   p.drawRoundedRect(cellRect, radius, radius);
//
//   // контур блока — чуть темнее базового цвета
//   QPen pen(base.darker(170));
//   pen.setWidthF(borderWidth);
//   pen.setJoinStyle(Qt::RoundJoin);
//   p.setPen(pen);
//   p.setBrush(Qt::NoBrush);
//   p.drawRoundedRect(cellRect.adjusted(borderWidth / 2, borderWidth / 2,
//                                       -borderWidth / 2, -borderWidth / 2),
//                     radius, radius);
//
//   // верхняя светлая полоска — имитация блика
//   p.setPen(Qt::NoPen);
//   QRectF topStripe(cellRect.left() + size * 0.12, cellRect.top() + size * 0.08,
//                    cellRect.width() - size * 0.24, cellRect.height() * 0.28);
//   QLinearGradient stripeGrad(topStripe.topLeft(), topStripe.bottomLeft());
//   stripeGrad.setColorAt(0.0, QColor(255, 255, 255, 180));
//   stripeGrad.setColorAt(1.0, QColor(255, 255, 255, 40));
//   p.setBrush(stripeGrad);
//   p.drawRoundedRect(topStripe, radius * 0.6, radius * 0.6);
// }
//
// QColor Tetris_Widget::colorForType(int type) const {
//   switch (type) {
//     case 1:
//       return QColor(10, 10, 10);  // 0 — пусто / фон клетки
//     case 2:
//       return QColor(200, 40, 40);  // 1 — красный
//     case 3:
//       return QColor(60, 200, 200);  // 2 — cyan
//     case 4:
//       return QColor(50, 80, 240);  // 3 — синий
//     case 5:
//       return QColor(240, 220, 60);  // 4 — желтый
//     case 6:
//       return QColor(240, 240, 240);  // 5 — белый / светлый
//     case 7:
//       return QColor(70, 200, 70);  // 6 — зеленый
//     default:
//       return QColor(200, 60, 200);  // 7 — magenta
//   }
// }
//
//
// void Tetris_Widget::print_info(QPainter& p, int level, int score,
//                                int high_score, int size) {
//     QRect infoRect(10 * size, 0, 8 * size, 6 * size);
//     p.save();
//     p.setRenderHint(QPainter::Antialiasing);
//
//     // фон панели
//     QLinearGradient bgGrad(infoRect.topLeft(), infoRect.bottomRight());
//     bgGrad.setColorAt(0.0, QColor(25, 25, 30));
//     bgGrad.setColorAt(1.0, QColor(15, 15, 20));
//     p.setBrush(bgGrad);
//     p.setPen(QPen(QColor(70, 70, 90), 2));
//     p.drawRoundedRect(infoRect, 10, 10);
//
//     // текст
//     QFont font = p.font();
//     font.setBold(true);
//     font.setPointSize(10);
//     p.setFont(font);
//
//     int y = infoRect.top() + size;
//     int lineStep = size * 1.5;
//
//     p.setPen(QColor("#00BFFF"));
//     p.drawText(infoRect.left() + size / 2, y, "High Score:");
//     y += lineStep;
//     p.setPen(Qt::white);
//     p.drawText(infoRect.left() + size / 2, y, QString::number(qMax(score, high_score)));
//
//     y += lineStep;
//     p.setPen(QColor("#00C000"));
//     p.drawText(infoRect.left() + size / 2, y, "Score:");
//     y += lineStep;
//     p.setPen(Qt::white);
//     p.drawText(infoRect.left() + size / 2, y, QString::number(score));
//
//     y += lineStep;
//     p.setPen(QColor("#FFBF00"));
//     p.drawText(infoRect.left() + size / 2, y, "Level:");
//     y += lineStep;
//     p.setPen(Qt::white);
//     p.drawText(infoRect.left() + size / 2, y, QString::number(level));
//
//     p.restore();
// }
//
//
// void Tetris_Widget::print_next(QPainter& p, int type, int size) {
//     int coords[8] = {};
//     generateTetraminoShape(coords, COMPLETE, type);
//     const int nextCols = 8;
//     const int nextRows = 2;
//     const int offsetCols = 10;  // отступ в клетках по ширине
//     const int offsetRows = 12;  // отступ в клетках по высоте
//
//     const int x0 =
//         offsetCols * size;  // пиксельная координата левого верхнего угла
//     const int y0 = offsetRows * size;
//
//     QRect nextRect(x0, y0, size * nextCols, size * nextRows);
//     p.save();
//     p.setRenderHint(QPainter::Antialiasing);
//     p.setRenderHint(QPainter::SmoothPixmapTransform);
//     // По умолчанию не рисуем контур при заполнении, потом рисуем контур отдельно
//     p.setPen(Qt::NoPen);
//
//     p.drawRect(nextRect);
//     p.restore();
//
//     // заголовок "NEXT" сверху (над полем)
//     p.setPen(Qt::black);
//     QFont f = p.font();
//     f.setBold(true);
//     p.setFont(f);
//     // Центрируем текст по ширине nextRect, отрисовываем чуть выше
//     p.drawText(
//         QRect(nextRect.left(), nextRect.top() - size, nextRect.width(), size),
//         Qt::AlignCenter, QStringLiteral("NEXT"));
//
//     // рисуем тетрамино по координатам (ожидаем 1-based координаты)
//     QColor fill = colorForType(type);
//     p.setPen(Qt::black);
//     p.setBrush(fill);
//
//     for (int i = 0; i < 8; i += 2) {
//         int x = coords[i];  // ожидание 1..10
//         int y = coords[i + 1] + 1;  // у вас в ncurses вы делали +5 — сохранил
//             // поведение (если не нужно, уберите +5)
//         // проверка границ (как у вас)
//         if (x < 1 || x > nextCols || y < 1 || y > nextRows) {
//             // при ошибке — можно отобразить текст в окне
//             p.setPen(Qt::red);
//             p.drawText(nextRect.adjusted(2, 2, -2, -2), Qt::AlignLeft | Qt::AlignTop,
//                        QString("smth wrong\nx:%1 y:%2").arg(x).arg(y));
//             continue;
//         }
//
//         int gridCol = x - 1;
//         int gridRow = y - 1;
//
//         QRect cell(nextRect.left() + gridCol * size,
//                    nextRect.top() + gridRow * size, size, size);
//
//         paint_tetramino(cell, type, p, size);
//     }
// }
//
void Tetris_Widget::print_game(QPainter& p, int** field, int** next, int size) {
  p.save();
  p.setPen(Qt::black);
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      int value = (field[i][j] != 0) ? field[i][j] : next[i][j];
      QRect cell(size * j, size * i, size, size);
      paint_tetramino(cell, value, p, size);
    }
  }
  p.restore();
}

void Tetris_Widget::paint_tetramino(QRectF cellRect, int value,
                                    QPainter& p, int size) {
  QColor c = colorForType(value);
  p.setBrush(c);
  p.drawRect(cellRect);
}

QColor Tetris_Widget::colorForType(int type) const {
  switch (type) {
    case 1: return QColor(200, 40, 40);   // красный
    case 2: return QColor(60, 200, 200);  // cyan
    case 3: return QColor(50, 80, 240);   // синий
    case 4: return QColor(240, 220, 60);  // желтый
    case 5: return QColor(240, 240, 240); // белый
    case 6: return QColor(70, 200, 70);   // зеленый
    case 7: return QColor(200, 60, 200);  // пурпурный
    default: return QColor(30, 30, 30);   // фон
  }
}

void Tetris_Widget::print_next(QPainter& p, int type, int size) {
  int coords[8] = {};
  generateTetraminoShape(coords, COMPLETE, type);
  const int x0 = 220;
  const int y0 = 40;
  const int nextCols = 4;
  const int nextRows = 4;

  QRect nextRect(x0, y0, size * nextCols, size * nextRows);
  p.save();
  p.setPen(Qt::black);
  p.setBrush(Qt::lightGray);
  p.drawRect(nextRect);

  p.setPen(Qt::black);
  p.drawText(QRect(nextRect.left(), nextRect.top() - size,
                   nextRect.width(), size),
             Qt::AlignCenter, "NEXT");

  for (int i = 0; i < 8; i += 2) {
    int x = coords[i] -2;
    int y = coords[i + 1] +2;
    if (x < 1 || x > nextCols || y < 1 || y > nextRows) continue;

    QRect cell(nextRect.left() + (x - 1) * size,
               nextRect.top() + (y - 1) * size, size, size);
    paint_tetramino(cell, type, p, size);
  }
  p.restore();
}

void Tetris_Widget::print_info(QPainter& p, int level, int score,
                               int high_score, int size) {
  int x0 = 220;
  int y0 = 120;
  p.save();
  p.setPen(Qt::black);
  p.setBrush(Qt::lightGray);
  QRect infoRect(x0, y0, 100, 100);
  p.drawRect(infoRect);

  p.setPen(Qt::black);
  p.drawText(infoRect.adjusted(5, 5, -5, -5), Qt::AlignTop | Qt::AlignLeft,
             QString("High: %1\nScore: %2\nLevel: %3")
             .arg(qMax(score, high_score))
             .arg(score)
             .arg(level));
  p.restore();
}



// using namespace :Qt;
void Tetris_Widget::keyPressEvent(QKeyEvent* e) {
  UserAction_t action = (UserAction_t)NONE_ACTION;
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
  // update_draw();
  if (action == Terminate) {
    QWidget::close();
  }
}
void Tetris_Widget::update_draw() {
  userInput((UserAction_t)NONE_ACTION, true);
  repaint();
}

void Tetris_Widget::closeEvent(QCloseEvent* event) {
  emit finished();
  *data = init_empty_data();
  QWidget::closeEvent(event);
}
