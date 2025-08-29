/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include "brick_game/brick_game.h"
#include "brick_game/tetris/game_api/game_api.h"
#include "brick_game/tetris/inc/tetramino_movement.h"
#include  "brick_game/tetris/inc/tetris.h"
#include "brick_game/tetris/inc/Timer.h"
#include "gui/cli/cli.h"
#include "gui/cli/tetris/frontend.h"

int main() {
    srand(time(0));
    // setup ncurses and windows
    init_nc();
    Tetris_wins_t *t_wins = get_tetris_wins();
    set_tetris_wins(t_wins);
    State *state = get_state();
    *state = start;

    // initialization game_info
    GameInfo_t *game_info = get_game_info_instance();
    *game_info = init_empty_gameInfo();
    int ch = -1;

    // initialize figure
    Tetramino *tetraMino = get_tetramino_instance();
    generateTetraminoShape(tetraMino->coordinates, tetraMino->rotate, tetraMino->type);

    // initialize timer
    Shift_timer *timer = get_shift_timer_instance();


    while (ch != 'q') {

        ch = getch();
        mvprintw(22, 13, "%c", ch);
        mvprintw(23, 13, "%s", stateToString(*state));
        mvprintw(24, 13, "delay: %lf",(double) timer->delay_to_shift);
        mvprintw(25, 13, "level: %d",game_info->level);
        mvprintw(26, 13, "speed: %lf",(double)game_info->speed);
        UserAction_t current_action = getSignal(ch);
        // movement hadle
        userInput(current_action, false);
        switch (*state) {
            case movement:
                if (isHorizontalMoveOrRotate(current_action) == MY_OK) {
                    onMoving(current_action);
                } else if (isDownMove(current_action)) {
                    onDownMoving(current_action);
                }
                break;
            case shift:
                if (timer->time_to_shift == true) {
                    onDownMoving(Down);
                    timer->time_to_shift = false;
                    gettimeofday(&timer->before, NULL);
                }
                break;

            // case spawn:
            //     next_tetramino(&tetraMino->r);
            //     state = get_state();
            //     break;

            case pause:
                while (getch()!= 'p') {
                    timeout(10);
                }
                *state = start;
                break;
            case game_over:
                while (getch()!= 'p') {
                    timeout(1000);
                }
                break;
            default:
                break;
                *state = shift;
        }
        draw_tetris(updateCurrentState(), *tetraMino);
        countTime(timer);
    };
}
