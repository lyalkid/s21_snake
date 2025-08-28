/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include "brick_game/brick_game.h"
#include "brick_game/tetris/inc/tetramino_movement.h"
#include  "brick_game/tetris/inc/tetris.h"
#include "brick_game/tetris/inc/TGM3Randomizer.h"
// #include "gui/cli/cli.h"
// #include "gui/cli/tetris/frontend.h"

int main() {
    // setup ncurses and windows
    // init_nc();
    // Tetris_wins_t* t_wins = get_tetris_wins();
    // set_tetris_wins(t_wins);

    // initialization game_info
    GameInfo_t *game_info = get_game_info();
    *game_info = init_empty_gameInfo();
    int ch = -1;
    Tetramino *tetraMino = get_tetramino_instance();
    TGM3Randomizer r;
    init_randomizer(&r);
    generateTetraminoShape(tetraMino->coordinates, tetraMino->rotate, tetraMino->type);
    int c = 0;
    int count[7] = {};
    while (ch != 'q') {
        // next_tetramino(&r);
        ch = getchar();
        moveTetramino(tetraMino, getSignal(ch));
        if (ch == '\n') {
            continue;
        }
        placeTetraminoInArray(*tetraMino, tetraMino->tmp_current_figure_on_field);
        // print_array(game_info->field);

        overlay_array(game_info->field, tetraMino->tmp_current_figure_on_field);
        printf("type %d\n", tetraMino->type);
        count[tetraMino->type - 1]++;
        printf("stats: ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", count[i]);
        }
        printf("\n");
        printf("%d \n", c);
        c++;
        int min_x =
                get_min(get_min(tetraMino->coordinates[0], tetraMino->coordinates[2]),
                        get_min(tetraMino->coordinates[4], tetraMino->coordinates[6])) +
                tetraMino->center_x;

        int max_x =
                get_max(get_max(tetraMino->coordinates[0], tetraMino->coordinates[2]),
                        get_max(tetraMino->coordinates[4], tetraMino->coordinates[6])) +
                tetraMino->center_x;
        print_array(tetraMino->tmp_current_figure_on_field, max_x, min_x);
    };
}
