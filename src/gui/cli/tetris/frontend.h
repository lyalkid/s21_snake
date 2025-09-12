/*
* @author Azamat G.
* @date 18.08.2025.
* @details
*
*/

#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../../brick_game/brick_game.h"
#include "../../../brick_game/tetris/inc/tetris.h"
#include "../cli.h"
void  draw_tetris(GameInfo_t currentState, Tetramino t);
void render_pause(WINDOW* game_win);
void render_game_over(WINDOW* game_win);
void render_game_win(WINDOW *win, int **field, int **next) ;
void render_next_win(WINDOW* next_win, int type);
void render_info_win(WINDOW* info_win, int h_score, int score, int level);
void draw_static(int state, Tetris_wins_t* t_wins) ;
void print_welcome_tetris(Tetris_wins_t* t_wins);



// void show_game_field(int** field, int** next, int score, int level);
//
// void draw_simple(State state, GameInfo_t gameInfo, Tetramino tetraMino);
//
// void init_ncurses(View* views);
// void init_colors();
// void terminate_ncurses(View* views);
//
// void render_game_win(WINDOW* win, int** field, int** next);
//
// void render_next_win(WINDOW* next_win, int type);
// void render_info_win(WINDOW* info_win, int h_score, int score, int level,
//                      int count[]);
// char piece(int type);
//
// void render_pause(WINDOW* game_field);
//
// void draw_static(Game_Objects_t* params);
// void draw_main(Game_Objects_t* params);
#endif //FRONTEND_H
