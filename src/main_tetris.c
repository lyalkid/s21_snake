/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include <stdbool.h>

#include "brick_game/brick_game.h"
#include "brick_game/tetris/game_api/game_api.h"
#include "brick_game/tetris/inc/Timer.h"
#include "brick_game/tetris/inc/tetramino_movement.h"
#include "brick_game/tetris/inc/tetris.h"
#include "gui/cli/cli.h"
#include "gui/cli/tetris/frontend.h"

int main() {
  srand(time(0));
  // setup ncurses and windows
  init_nc();
  Tetris_wins_t *t_wins = get_tetris_wins();
  set_tetris_wins(t_wins);

  // initialization TetrisData
  TetrisData_t *data = get_data();
  int ch = 0;
  bool game_run = true;
  Tetris_state prev_state = STATE_START;

  while (game_run && data != NULL) {
    draw_static(data->current_state, t_wins);
    ch = getch();
    data->current_action = getSignal(ch);
    mvprintw(23, 13, "%s", stateToString(data->current_state));

    if (data->current_action == Start) {
      data->current_state = prev_state;
      data->current_game_info.pause = 0;
      while (data->current_game_info.pause == 0 &&
             data->current_state != STATE_EXIT) {
        ch = getch();
        mvprintw(23, 13, "%s", stateToString(data->current_state));
        mvprintw(24, 13, "delay: %lf",
                 (double)data->shift_timer.delay_to_shift);

        data->current_action = getSignal(ch);

        // handle input
        userInput(data->current_action, false);
        // fsm, draw

        draw_tetris(updateCurrentState(), data->current_tetraMino);
        countTime(&data->shift_timer);
        if (data->current_game_info.pause == 1) {
          prev_state = data->current_state;
          data->current_state = STATE_PAUSE;
        }
        // data->current_action = NONE_ACTION;
      }
    } else if (ch == 'q') {
      game_run = false;

      free(data);
    }
  }
  terminate_ncurses();
}
