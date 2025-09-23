/*
 * @author Azamat G.
 * @date 13.09.2025.
 * @details
 *
 */

#include "Snake.h"

namespace s21 {
Snake::Snake() {
  width = WIDTH;
  height = HEIGHT;
  reset();
}

void Snake::reset() {
  int startX = 5, startY = 0;
  head = {startX, startY};
  score = 4;
  dir = {1, 0};
  direction_changed = false;
  for (int i = 0; i < score; i++) {
    body[i] = {startX - i, startY};  // голова справа, хвост слева
  }
  spawn_berry();
}

void Snake::changeDirection(UserAction_t action) {
  Vec2 tmp = dir;
  if (action == Left && dir.x != 1) {
    dir.x = -1;
    dir.y = 0;
  }
  if (action == Right && dir.x != -1) {
    dir.x = +1;
    dir.y = 0;
  }
  if (action == Down && dir.y != -1) {
    dir.x = 0;
    dir.y = +1;
  }
  if (action == Up && dir.y != 1) {
    dir.x = 0;
    dir.y = -1;
  }
  if (tmp.x != dir.x || tmp.y != dir.y) {
    direction_changed = true;
  }
}

void Snake::update(int **field) {
  for (int i = score; i >= 0; i--) {
    body[i] = body[i - 1];
  }
  // body[0] = head;

  head.x += dir.x;
  if (head.x < 0)
    head.x += 1;
  else if (head.x >= width)
    head.x -= 1;
  head.y += dir.y;
  if (head.y < 0)
    head.y += 1;
  else if (head.y >= height)
    head.y -= 1;
  if (head.x == berry.x && head.y == berry.y) {
    score++;
    while (true) {
      berry.x = rand() % width;
      berry.y = rand() % height;
      if (field[berry.y][berry.x] == 0) break;
    }
  }
  body[0] = head;
}

void Snake::spawn_berry() { berry = {rand() % width, rand() % height}; }
}  // namespace s21
