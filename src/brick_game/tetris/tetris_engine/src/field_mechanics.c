/*
 * @author Azamat G.
 * @date 14.08.2025.
 * @details
 *
 */

#include "../inc/tetris.h"

int removeFullLines(int** field, int rows, int cols) {
  int count = 0;
  int full_scan = 0;
  while (full_scan != 2) {
    int flag = 1;
    for (int i = rows - 1; i >= 0; i--) {
      int destroy = isLineFull(field[i], cols);
      if (destroy == YES) {
        removeLine(field, cols, i);
        count++;
        flag = 0;
      }
    }
    if (flag == 1) full_scan++;
  }
  return count;
}
int isLineFull(const int a[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (a[i] != 0) sum++;
  }
  return sum == size ? YES : NO;
}
void removeLine(int** field, int cols, int row_not) {
  for (int i = 0; i < cols; i++) {
    field[row_not][i] = 0;
  }
  for (int j = 0; j < cols; j++) {
    for (int i = row_not; i > 0; i--) {
      //        int tmp_a = field[i][j];
      int tmp_b = field[i - 1][j];
      field[i][j] = tmp_b;
    }
  }
}
