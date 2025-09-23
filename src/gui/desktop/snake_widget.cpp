#include "snake_widget.h"

Snake_Widget::Snake_Widget(QWidget *parent) : QWidget{parent} {
  setFixedSize(350, 400);
  setWindowTitle("Snake");
  timer = new QTimer;

  connect(timer, &QTimer::timeout, this, &Snake_Widget::update_draw);
  timer->start(1);
}

// void Snake_Widget::paintEvent(QPaintEvent *e) {
//     Q_UNUSED(e)
//     QPainter p(this);
//     GameInfo_t inf = controller.updateCurrentState();
//     int **field = inf.field;
//     int size = 20;
//     Snake_state state = controller.get_state();

//     if (state == INIT || state == PAUSE || state == GAME_OVER || state ==
//     WON) {
//         print_welcome(p, state);
//     } else {
//         for (int i{}; i < HEIGHT; ++i) {
//             for (int j{}; j < WIDTH; ++j) {
//                 int res = inf.field[i][j];
//                 if (res == BERRY) {
//                     p.setBrush(Qt::red);
//                 } else if (res == HEAD) {
//                     p.setBrush(Qt::yellow);
//                 }
//                 else if(res ==SNAKE ){
//                     p.setBrush(Qt::green);
//                 }
//                 else{
//                     p.setBrush(Qt::black);
//                 }
//                 p.drawRect(size * j, size * i, size, size);
//             }
//         }
//     }
// }

void Snake_Widget::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing, true);
  GameInfo_t inf = controller.updateCurrentState();
  int **field = inf.field;
  const int size = 20;
  Snake_state state = controller.get_state();

  // исправленная проверка состояний
  if (state == INIT || state == PAUSE || state == GAME_OVER || state == WON) {
    print_welcome(p, state);
    return;
  }

  // фон поля
  p.fillRect(rect(), QColor(18, 18, 20));

  // лёгкая сетка фона (не обязательна, можно убрать)
  p.setPen(QColor(25, 25, 30));
  for (int i = 0; i <= HEIGHT; ++i) {
    p.drawLine(0, i * size, WIDTH * size, i * size);
  }
  for (int j = 0; j <= WIDTH; ++j) {
    p.drawLine(j * size, 0, j * size, HEIGHT * size);
  }

  // рисуем клетки
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      int val = field[i][j];
      QRectF cellF(j * size, i * size, size, size);
      // небольшой отступ внутри клетки для "воздушности"
      QRectF inner = cellF.adjusted(2, 2, -2, -2);
      qreal r =
          std::min(inner.width(), inner.height()) * 0.25;  // радиус скругления

      if (val == SNAKE) {
        // тело: вертикальный градиент зелёного
        QLinearGradient grad(inner.topLeft(), inner.bottomLeft());
        grad.setColorAt(0.0, QColor(120, 220, 120));
        grad.setColorAt(1.0, QColor(30, 140, 30));
        p.setPen(Qt::NoPen);

        // лёгкая тень под сегментом
        QRectF shadow = inner.translated(1.2, 1.8);
        p.setBrush(QColor(0, 0, 0, 40));
        p.drawRoundedRect(shadow, r, r);

        p.setBrush(grad);
        p.drawRoundedRect(inner, r, r);

        // бликовая полоска сверху
        QRectF shine = inner;
        shine.setHeight(inner.height() * 0.45);
        QLinearGradient sgrad(shine.topLeft(), shine.bottomLeft());
        sgrad.setColorAt(0.0, QColor(255, 255, 255, 120));
        sgrad.setColorAt(1.0, QColor(255, 255, 255, 10));
        p.setBrush(sgrad);
        p.drawRoundedRect(shine, r * 0.9, r * 0.9);

        // тонкая внешняя обводка
        p.setPen(QColor(10, 60, 10, 180));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(inner, r, r);
      } else if (val == HEAD) {
        // голова: желто-оранжевый градиент + глаза
        QLinearGradient grad(inner.topLeft(), inner.bottomLeft());
        grad.setColorAt(0.0, QColor(255, 240, 120));
        grad.setColorAt(1.0, QColor(220, 140, 20));
        p.setPen(Qt::NoPen);

        // тень
        QRectF shadow = inner.translated(1.5, 2.0);
        p.setBrush(QColor(0, 0, 0, 60));
        p.drawRoundedRect(shadow, r, r);

        p.setBrush(grad);
        p.drawRoundedRect(inner, r, r);

        // блик на голове
        QRectF blink =
            inner.adjusted(inner.width() * 0.08, inner.height() * 0.08,
                           -inner.width() * 0.5, -inner.height() * 0.5);
        QRadialGradient rg(blink.center(), blink.width() * 0.9, blink.center());
        rg.setColorAt(0.0, QColor(255, 255, 255, 200));
        rg.setColorAt(1.0, QColor(255, 255, 255, 0));
        p.setBrush(rg);
        p.drawEllipse(blink);

        // глаза (два белых кружка с чёрными зрачками)
        qreal eyeR = size * 0.12;
        QPointF leftEye(inner.left() + inner.width() * 0.32,
                        inner.top() + inner.height() * 0.35);
        QPointF rightEye(inner.left() + inner.width() * 0.68 - eyeR,
                         inner.top() + inner.height() * 0.35);
        p.setBrush(Qt::white);
        p.setPen(Qt::NoPen);
        p.drawEllipse(leftEye, eyeR, eyeR);
        p.drawEllipse(rightEye, eyeR, eyeR);

        p.setBrush(Qt::black);
        qreal pupilR = eyeR * 0.5;
        p.drawEllipse(
            QPointF(leftEye.x() + pupilR * 0.4, leftEye.y() + pupilR * 0.1),
            pupilR, pupilR);
        p.drawEllipse(
            QPointF(rightEye.x() + pupilR * 0.4, rightEye.y() + pupilR * 0.1),
            pupilR, pupilR);

        // тонкая тёмная обводка головы
        p.setPen(QColor(80, 50, 20, 200));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(inner, r, r);
      } else if (val == BERRY) {
        // ягода: насыщенный красный с радиальным светом
        p.setPen(Qt::NoPen);
        QRectF berryRect = inner;
        // базовая тень
        QRectF shadow = berryRect.translated(1.8, 2.2);
        p.setBrush(QColor(0, 0, 0, 70));
        p.drawEllipse(shadow);

        QRadialGradient grad(
            berryRect.center() -
                QPointF(berryRect.width() * 0.12, berryRect.height() * 0.18),
            berryRect.width() * 0.7);
        grad.setColorAt(0.0, QColor(255, 180, 180));
        grad.setColorAt(0.5, QColor(220, 20, 20));
        grad.setColorAt(1.0, QColor(120, 10, 10));
        p.setBrush(grad);
        p.drawEllipse(berryRect);

        // блик
        QRectF shine = berryRect.adjusted(
            berryRect.width() * 0.08, berryRect.height() * 0.06,
            -berryRect.width() * 0.5, -berryRect.height() * 0.5);
        QRadialGradient shineG(shine.center(), shine.width() * 0.9,
                               shine.center());
        shineG.setColorAt(0.0, QColor(255, 255, 255, 200));
        shineG.setColorAt(1.0, QColor(255, 255, 255, 0));
        p.setBrush(shineG);
        p.drawEllipse(shine);

        // хвостик ягодки (маленькая зелёная веточка)
        QPen stemPen(QColor(40, 140, 40), 2, Qt::SolidLine, Qt::RoundCap);
        p.setPen(stemPen);
        QPointF s1(berryRect.center().x() + berryRect.width() * 0.18,
                   berryRect.top() + berryRect.height() * 0.05);
        QPointF s2 = s1 + QPointF(6, -6);
        QPointF s3 = s1 + QPointF(10, -2);
        p.drawLine(s1, s2);
        p.drawLine(s1, s3);
      } else {
        // пустая клетка — тёмный фон с лёгким градиентом
        QLinearGradient g(cellF.topLeft(), cellF.bottomLeft());
        g.setColorAt(0.0, QColor(16, 16, 18));
        g.setColorAt(1.0, QColor(12, 12, 14));
        p.setBrush(g);
        p.setPen(Qt::NoPen);
        p.drawRect(cellF);
      }
    }
  }

  // рамка вокруг поля
  p.setPen(QPen(QColor(80, 80, 90), 2));
  p.setBrush(Qt::NoBrush);
  p.drawRect(0, 0, WIDTH * size, HEIGHT * size);
  // --- боковая панель (справа) ---
  const int sideW = 160;  // ширина панели
  QRectF sideRect(WIDTH * size + 12, 8, sideW - 8, HEIGHT * size - 16);

  // фон панели
  QLinearGradient sideG(sideRect.topLeft(), sideRect.bottomLeft());
  sideG.setColorAt(0.0, QColor(28, 28, 30));
  sideG.setColorAt(1.0, QColor(20, 20, 22));
  p.setBrush(sideG);
  p.setPen(Qt::NoPen);
  p.drawRoundedRect(sideRect, 6, 6);

  // Отступы внутри панели
  const int pad = 12;
  QRectF content = sideRect.adjusted(pad, pad, -pad, -pad);

  // Заголовок
  QFont titleF = p.font();
  titleF.setPointSize(12);
  titleF.setBold(true);
  p.setFont(titleF);
  p.setPen(QColor(220, 220, 230));
  p.drawText(content.left(), content.top(), content.width(), 24,
             Qt::AlignLeft | Qt::AlignVCenter, QStringLiteral("GAME"));

  // Счёт (score)
  QFont labelF = p.font();
  labelF.setPointSize(10);
  labelF.setBold(false);
  p.setFont(labelF);

  qreal y = content.top() + 28;

  // рисуем иконку ягоды слева
  qreal iconR = 12;
  QPointF iconCenter(content.left() + iconR, y + iconR);
  QRadialGradient berryG(iconCenter - QPointF(iconR * 0.25, iconR * 0.2),
                         iconR * 1.0);
  berryG.setColorAt(0.0, QColor(255, 180, 180));
  berryG.setColorAt(0.5, QColor(220, 20, 20));
  berryG.setColorAt(1.0, QColor(120, 10, 10));
  p.setBrush(berryG);
  p.setPen(Qt::NoPen);
  p.drawEllipse(QRectF(iconCenter.x() - iconR, iconCenter.y() - iconR,
                       2 * iconR, 2 * iconR));

  // текст "Score"
  p.setPen(QColor(200, 200, 210));
  p.drawText(content.left() + iconR * 2 + 8, y,
             content.width() - (iconR * 2 + 8), 20,
             Qt::AlignLeft | Qt::AlignVCenter, QStringLiteral("Score"));

  // значение score (большими)
  QFont valF = p.font();
  valF.setPointSize(18);
  valF.setBold(true);
  p.setFont(valF);

  // берем значения из inf (адаптируйте имена, если отличаются)
  int scoreVal = inf.score;
  int levelVal = inf.level;
  int highScoreVal = inf.high_score;

  p.setPen(QColor(255, 235, 120));
  p.drawText(content.left(), y + 22, content.width(), 36,
             Qt::AlignLeft | Qt::AlignVCenter, QString::number(scoreVal));

  // High Score (под Score)
  qreal hsY = y + 62;
  qreal trophyR = 8;
  QPointF trophyCenter(content.left() + trophyR, hsY + trophyR - 2);

  // простой трофей (жёлтый кружок + "T")
  QLinearGradient trG(trophyCenter - QPointF(trophyR * 0.4, trophyR * 0.4),
                      trophyCenter + QPointF(trophyR * 0.4, trophyR * 0.4));
  trG.setColorAt(0.0, QColor(255, 230, 120));
  trG.setColorAt(1.0, QColor(200, 140, 20));
  p.setBrush(trG);
  p.setPen(Qt::NoPen);
  p.drawEllipse(QRectF(trophyCenter.x() - trophyR, trophyCenter.y() - trophyR,
                       2 * trophyR, 2 * trophyR));

  // буква T поверх (иконка)
  p.setPen(QColor(80, 40, 0));
  QFont tF = p.font();
  tF.setPointSize(8);
  tF.setBold(true);
  p.setFont(tF);
  p.drawText(QRectF(trophyCenter.x() - trophyR, trophyCenter.y() - trophyR,
                    2 * trophyR, 2 * trophyR),
             Qt::AlignCenter, QStringLiteral("T"));

  // текст "High Score"
  p.setFont(labelF);
  p.setPen(QColor(200, 200, 210));
  p.drawText(content.left() + trophyR * 2 + 10, hsY - 2,
             content.width() - (trophyR * 2 + 10), 18,
             Qt::AlignLeft | Qt::AlignVCenter, QStringLiteral("High Score"));

  // значение high score
  p.setFont(valF);
  p.setPen(QColor(240, 200, 120));
  p.drawText(content.left(), hsY + 12, content.width(), 28,
             Qt::AlignLeft | Qt::AlignVCenter, QString::number(highScoreVal));

  // линия-разделитель
  y += 110;
  p.setPen(QColor(60, 60, 70));
  p.drawLine(content.left(), y, content.right(), y);
  y += 12;

  // Level
  p.setFont(labelF);
  p.setPen(QColor(200, 200, 210));
  p.drawText(content.left(), y, content.width(), 20,
             Qt::AlignLeft | Qt::AlignVCenter, QStringLiteral("Level"));

  p.setFont(valF);
  p.setPen(QColor(160, 220, 160));
  p.drawText(content.left(), y + 20, content.width(), 36,
             Qt::AlignLeft | Qt::AlignVCenter, QString::number(levelVal));
}

void Snake_Widget::print_welcome(QPainter &p, Snake_state state) {
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
  if (state == INIT) {
    p.drawText(titleRect, Qt::AlignCenter, "SNAKE");
    p.drawText(subRect, Qt::AlignCenter,
               "Нажмите n чтобы начать\nWASD — перемещение, f — поворот");
  } else if (state == GAME_OVER) {
    p.drawText(titleRect, Qt::AlignCenter, "GAME_OVER");
    p.drawText(
        subRect, Qt::AlignCenter,
        "Нажмите n чтобы начать сначала\nWASD — перемещение, f — поворот");
  } else if (state == PAUSE) {
    p.drawText(titleRect, Qt::AlignCenter, "PAUSE");
    p.drawText(subRect, Qt::AlignCenter,
               "Нажмите p чтобы начать\nWASD — перемещение, f — поворот");
  } else if (state == WON) {
    p.drawText(titleRect, Qt::AlignCenter, "YOU WON");
    p.drawText(subRect, Qt::AlignCenter,
               "Нажмите n чтобы начать\nWASD — перемещение, f — поворот");
  }
  p.restore();
}

void Snake_Widget::keyPressEvent(QKeyEvent *e) {
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
    case Qt::Key_Return:
      action = Action;
      break;
    default:
      // action = (UserAction_t)NONE_ACTION;
      break;
  }

  controller.userInput(action, false);

  // update_draw();
  if (action == Terminate) {
    QWidget::close();
  }
}

void Snake_Widget::update_draw() {
  controller.userInput((UserAction_t)NONE_ACTION, true);
  countTime(&controller.timer);
  repaint();
}

void Snake_Widget::closeEvent(QCloseEvent *event) {
  emit finished_snake();
  QWidget::closeEvent(event);
}
