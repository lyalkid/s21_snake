/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include <stdbool.h>

#include "../../../brick_game/brick_game.h"
// #include "brick_game/tetris/inc/game_api.h"
#include "../../../brick_game/tetris/inc/tetramino_movement.h"
#include "../../../brick_game/tetris/inc/tetris.h"
#include "../../../brick_game/utils/timer.h"
#include "../cli.h"
#include "frontend.h"

void debug_info(Tetris_state_t current_state, Tetris_state_t previous_state) {
    mvprintw(23, 13, "current: %s", stateToString(current_state));
    mvprintw(24, 13, "prev: %s", stateToString(previous_state));
    // mvprintw(25, 13, "action: %s", actionToString(action));
}



void game_loop(Game_wins_t *t_wins) {
    srand(time(0));

    TetrisData_t *data = get_data();
    int ch;
    UserAction_t action = NONE_ACTION;

    while (data->is_active) {
        ch = getch();
        action = getSignal(ch);

        userInput(action, false);
        countTime(&data->shift_timer);
        // if (data->shift_timer.time_to_shift) usleep(200000 );
        draw(data, t_wins);
        debug_info(data->current_state, data->current_state);

        // =======================
        // Управление состояниями
        // =======================
        if (data->current_state == STATE_GAME_OVER) {
            if (action == Start) {
                reset_game(data);
                data->current_state = STATE_SPAWN;
            } else if (action == Terminate) {
                finish_game(data);
            }
        }

        if (data->current_state == STATE_EXIT) {
            break;
        }
    }

}


int main() {
    init_nc();
    Game_wins_t t_wins = {0};
    set_tetris_wins(&t_wins);

    game_loop(&t_wins);

    terminate_ncurses(&t_wins);
}
