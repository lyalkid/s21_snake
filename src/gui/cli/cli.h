//
// Created by Azamat G. on 08.08.2025.
//


#ifndef CLI_H
#define CLI_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef __WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
# include "../../brick_game/brick_game.h"
#include "../../brick_game/tetris/inc/tetris.h"


#define ITEMS 3
#define CONTROL_UP 'w'
#define CONTROL_DOWN 's'
#define CONTROL_NEXT '\n'
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


void init_nc();
void set_tetris_wins(Tetris_wins_t* views);
void init_colors();
void terminate_ncurses();

int handle_menu() ;
void print_menu(WINDOW *menu_win, int highlight, const char **choices);
void init_menu();
void set_title(WINDOW* title_win, char* title);
Game_wins_t* get_game_wins() ;
void cleanup_game_wins();
Tetris_wins_t init_tetris_wins();
Tetris_wins_t* get_tetris_wins();
#endif //CLI_H
