/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */
#include "brick_game/brick_game.h"
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
    int c = 0;
    int count[7] = {};
    while (ch != 'q') {
        next_tetramino(&r);

        ch = getchar();
        if (ch == '\n') {
            continue;
        }
        print_array(game_info->field);
        printf("type %d\n", tetraMino->type);
        count[tetraMino->type - 1]++;
        printf("stats: ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", count[i]);
        }
        printf("\n");
        printf("%d ", c);
        c++;
    };
}
