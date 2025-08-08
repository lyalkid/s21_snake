//
// Created by Azamat G. on 08.08.2025.
//


#ifndef CLI_H
#define CLI_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#define ITEMS 4
#define HEIGHT 20
#define WIDTH 10
#define scale_field 2
#define scale 2

#define FIELD_Y HEIGHT + 2
#define FIELD_X WIDTH* scale_field + 2

#define NEXT_FIELD 10
#define INFO_FIELD 10

#define INFO_X INFO_FIELD* scale + 2
#define INFO_Y INFO_FIELD + 2

#define NEXT_X NEXT_FIELD* scale + 2
#define NEXT_Y NEXT_FIELD


#define CONTROL_UP 'w'
#define CONTROL_DOWN 's'
#define CONTROL_NEXT '\n' // Enter
typedef struct {
    int yMax;
    int xMax;
    WINDOW* game_win;
    WINDOW* info_win;
    WINDOW* next_win;
} Tetris_wins_t;

typedef struct {
    WINDOW* title_win;
    WINDOW* menu_win;
    WINDOW* info_win;
}Game_wins_t;

/*!
    \brief Родительский класс, не несущий никакой смысловой нагрузки

    Данный класс имеет только одну простую цель: проиллюстрировать то,
    как Doxygen документирует наследование
*/
void init_nc();
void set_tetris_wins(Tetris_wins_t* views);
void init_colors();
void terminate_ncurses();

int menu() ;
void print_menu(WINDOW *menu_win, int highlight, const char **choices);
void set_title(WINDOW* title_win, char* title);
Game_wins_t* get_game_wins() ;
void cleanup_game_wins(Game_wins_t* game_wins);
Tetris_wins_t init_tetris_wins();
Tetris_wins_t* get_tetris_wins();

#endif //CLI_H
