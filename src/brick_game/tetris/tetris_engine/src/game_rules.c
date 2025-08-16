/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#include "../inc/tetris.h"
int calc_score(int lines) {
  int res = 0;
  if (lines != 0) {
    switch (lines) {
      case 1:
        res = 100;
        break;
      case 2:
        res = 300;
        break;
      case 3:
        res = 700;
        break;
      default:
        res = 1500;
        break;
    }
  }
  return res;
}
int calc_level(int current_score) {
  int res = current_score / 600;
  return res > 10 ? 10 : res;
}