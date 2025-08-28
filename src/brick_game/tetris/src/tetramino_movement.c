/*
 * @author Azamat G.
 * @date 14.08.2025.
 * @details
 *
 */

#include "../inc/tetramino_movement.h"

int canMoveTetramino(Tetramino tetraMino, int** field, UserAction_t key) {
  int** next = malloc_array(HEIGHT, WIDTH);
  int** tmp_next = malloc_array(HEIGHT, WIDTH);

  int** tmp_field = malloc_array(HEIGHT, WIDTH);
  placeTetraminoInArray(tetraMino, next);
  moveTetramino(&tetraMino, key);
  placeTetraminoInArray(tetraMino, next);

  bin_array(next, tmp_next, HEIGHT, WIDTH);

  bin_array(field, tmp_field, HEIGHT, WIDTH);
  int is_all_ok_val = canMergeFigures(tmp_field, tmp_next);
  free_array(tmp_next, HEIGHT);
  free_array(tmp_field, HEIGHT);
  free_array(next, HEIGHT);

  return is_all_ok_val;
}
int is_rotate_possible(Tetramino tetraMino, int rotate) {
  int possible = 1;
  tetraMino.rotate = rotate;
  generateTetraminoShape(tetraMino.coordinates, tetraMino.rotate,
                         tetraMino.type);
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMino.coordinates[i] + tetraMino.center_x;
    int y = tetraMino.coordinates[i + 1] + tetraMino.center_y;
    if (x < 0 || x >= WIDTH || y >= HEIGHT || y < 0) {
      possible = 0;
      break;
    }
  }
  return possible;
}
int isHorizontalMoveOrRotate(UserAction_t userAction) {
  int res = MY_OK;
  if (!(userAction == Left || userAction == Right || userAction == Action))
    res = ERROR;
  return res;
}
int isDownMove(UserAction_t userAction) {
  int res = MY_OK;
  if (userAction == Down) {
    res = ERROR;
  }
  return res;
}

void moveTetramino(Tetramino* tetraMino, UserAction_t key) {
  // TODO уменьшить размер строк

  int min_x =
      get_min(get_min(tetraMino->coordinates[0], tetraMino->coordinates[2]),
              get_min(tetraMino->coordinates[4], tetraMino->coordinates[6])) +
      tetraMino->center_x;

  int max_x =
      get_max(get_max(tetraMino->coordinates[0], tetraMino->coordinates[2]),
              get_max(tetraMino->coordinates[4], tetraMino->coordinates[6])) +
      tetraMino->center_x;
  switch (key) {
    case Left:
      if ((min_x - 1) >= 0) tetraMino->center_x -= 1;
      break;

    case Right:
      if ((max_x + 1 < WIDTH)) tetraMino->center_x += 1;
      break;
    case Action:
      rotate_TetraMino(tetraMino);
      break;
      case Down:
        move_down_tetraMino(tetraMino);
      break;
    default:
      break;
  }
}

void move_down_tetraMino(Tetramino* tetraMino) { tetraMino->center_y += 1; }

void move_up_tetraMino(Tetramino* tetraMino) {
  if (tetraMino->center_y >= HEIGHT - 1) tetraMino->center_y -= 1;
}
void rotate_TetraMino(Tetramino* tetraMino) {
  int rotate = (tetraMino->rotate + 1) % 4;

  if (is_rotate_possible(*tetraMino, rotate)) {
    tetraMino->rotate = rotate;
    generateTetraminoShape(tetraMino->coordinates, tetraMino->rotate,
                           tetraMino->type);
  }
}