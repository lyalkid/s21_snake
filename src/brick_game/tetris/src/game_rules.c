/*
 * @author Azamat G.
 * @date 15.08.2025.
 * @details
 *
 */

#include <math.h>

#include "../../utils/defines.h"
#include "../../utils/utilities.h"
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

void game_mechanics(TetrisData_t* data) {
  GameInfo_t* game_info = &data->current_game_info;
  // calc score
  game_info->score +=
      calc_score(removeFullLines(game_info->field, HEIGHT, WIDTH));
  game_info->level = calc_level(game_info->score);
  game_info->speed = TIME * pow(0.9, game_info->level);
  data->shift_timer.delay_to_shift = (long)game_info->speed;

  if (game_info->level == 10) data->is_win = true;
  if (get_data()->current_game_info.score >
      get_data()->current_game_info.high_score)
    write_high_score(get_data()->current_game_info.score, 1);
}