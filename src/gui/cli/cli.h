//
// Created by Azamat G. on 08.08.2025.
//

#ifndef CLI_H
#define CLI_H
#include <stdbool.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 10

typedef struct {
    int yMax;
    int xMax;
#ifndef debug
    WINDOW* game_win;
    WINDOW* info_win;
    WINDOW* next_win;
    #endif
} View;

void init_ncurses(View* views);

void draw();
#endif //CLI_H
