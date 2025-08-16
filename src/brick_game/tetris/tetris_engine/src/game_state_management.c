/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */
#include "../inc/tetris.h"

GameInfo_t init_empty_gameInfo() {
  GameInfo_t gameInfo = {0};
  gameInfo.score = 0;
  gameInfo.high_score = 0;
  gameInfo.level = 0;
  gameInfo.pause = 0;
  gameInfo.speed = 0;
  gameInfo.field = malloc_array(HEIGHT, WIDTH);
  gameInfo.next = malloc_array(NEXT_FIELD, NEXT_FIELD);
  return gameInfo;
}
int mergeFigureIntoField(int** next, int** field) {
  int is_all_ok_val = canMergeFigures(field, next);
  if (is_all_ok_val) {
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        int n_tmp = next[i][j];
        int f_tmp = field[i][j];
        int res = n_tmp + f_tmp;
        field[i][j] = res;
      }
    }
  }
  return is_all_ok_val;
}
int checkCollisionWithWallsOrBlocks(Tetramino tetraMino, int** field) {
  int is_all_ok_val = MY_OK;
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMino.coordinates[i] + tetraMino.center_x;
    int y = tetraMino.coordinates[i + 1] + tetraMino.center_y;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
      is_all_ok_val = ERROR;
      break;
    }
  }
  if (is_all_ok_val == MY_OK) {
    int** tmp_next = malloc_array(HEIGHT, WIDTH);
    placeTetraminoInArray(tetraMino, tmp_next);
    is_all_ok_val = canMergeFigures(field, tmp_next);
    free_array(tmp_next, HEIGHT);
  }
  return is_all_ok_val;
}
int canMergeFigures(int** field, int** next) {
  int** tmp_next = malloc_array(HEIGHT, WIDTH);

  int** tmp_field = malloc_array(HEIGHT, WIDTH);
  bin_array(next, tmp_next, HEIGHT, WIDTH);

  bin_array(field, tmp_field, HEIGHT, WIDTH);
  int is_all_ok_val = MY_OK;

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int n_tmp = tmp_next[i][j];
      int f_tmp = tmp_field[i][j];
      int res = n_tmp + f_tmp;
      if (res > 1) {
        is_all_ok_val = ERROR;
        break;
      }
    }
    if (is_all_ok_val == ERROR) break;
  }
  free_array(tmp_field, HEIGHT);
  free_array(tmp_next, HEIGHT);

  return is_all_ok_val;
}
