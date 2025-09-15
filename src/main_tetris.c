/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include <stdbool.h>

#include "brick_game/brick_game.h"
// #include "brick_game/tetris/inc/game_api.h"
#include "brick_game/tetris/inc/tetramino_movement.h"
#include "brick_game/tetris/inc/tetris.h"
#include "brick_game/tetris/inc/timer.h"
#include "gui/cli/cli.h"
#include "gui/cli/tetris/frontend.h"

void debug_info(Tetris_state_t current_state, Tetris_state_t previous_state,
                UserAction_t action) {
    mvprintw(23, 13, "current: %s", stateToString(current_state));
    mvprintw(24, 13, "prev: %s", stateToString(previous_state));
    mvprintw(25, 13, "action: %s", actionToString(action));
}

void out(int **field, int **next) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int res = field[i][j] + next[i][j];
            if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
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

        draw(data, t_wins);
        debug_info(data->current_state, data->current_state, action);

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

    free_game(data);
}


int main() {
    init_nc();
    Game_wins_t t_wins = {0};
    set_tetris_wins(&t_wins);

    game_loop(&t_wins);

    terminate_ncurses(&t_wins);
}


// bool game_run = true;
//
// while (game_run && data != NULL) {
//     main_menu_fsm(data);
//     draw_static(data->current_state, &t_wins);
//     data->current_action = getSignal(getch());
//     debug_info(data->current_state, prev_state, data->current_action);
//
//     if (data->current_action == Start) {
//         timeout(0);
//         data->current_state = prev_state;
//         data->current_game_info.pause = 0;
//         while (data->current_state != STATE_PAUSE &&
//                data->current_state != STATE_MAIN_MENU &&
//                data->current_state != STATE_EXIT &&
//                data->current_state != STATE_GAME_OVER) {
//             debug_info(data->current_state, prev_state, data->current_action);
//             data->current_action = getSignal(getch());
//             // handle input
//             userInput(data->current_action, false);
//             // fsm
//             game_fsm(TODO);
//             // draw
//             draw_tetris(updateCurrentState(), data->current_tetraMino, &t_wins);
//             countTime(&data->shift_timer);
//             if (data->current_game_info.pause == 1) {
//                 prev_state = data->current_state;
//                 data->current_state = STATE_PAUSE;
//             }
//             // data->current_action = NONE_ACTION;
//                }
//         // usleep(160000);
//         // } else if (ch == 'q') {
//         //   game_run = false;
//         //
//         //   free(data);
//     }
// }
// delwin(t_wins.game_win);
//
// delwin(t_wins.info_win);
//
// delwin(t_wins.next_win);
//
// terminate_ncurses();
// system("clear");
// printf("end!");
