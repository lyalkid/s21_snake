//
// Created by Azamat G. on 08.08.2025.
//
#include "cli.h"

// #include <curses.h>
#include <stdio.h>
void init_nc() {
  initscr();
  cbreak();
  noecho();
  int h = 0, w = 0;

  init_colors();

  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(1000);
}

/**
 * @brief Двигает фигуру влево.
 */
Tetris_wins_t init_tetris_wins() {
  Tetris_wins_t views = {};
  getmaxyx(stdscr, views.yMax, views.xMax);
  // delwin(views.game_win);
  return views;
}
void set_tetris_wins(Tetris_wins_t* views) {
  views->game_win = newwin(FIELD_Y, FIELD_X, 0, 0);
  views->info_win = newwin(INFO_Y - 2, INFO_X, 0, FIELD_X);
  views->next_win = newwin(NEXT_Y + 2, NEXT_X, INFO_Y - 2, FIELD_X);
  refresh();
  box(views->game_win, 0, 0);
  box(views->info_win, 0, 0);
  box(views->next_win, 0, 0);
  wrefresh(views->game_win);
  wrefresh(views->info_win);
  wrefresh(views->next_win);
  refresh();
}

void init_colors() {
  start_color();
  init_pair(9, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_BLUE);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(6, COLOR_BLACK, COLOR_GREEN);
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
}

void terminate_ncurses() {
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран
  refresh();
  refresh();
  endwin();
}

Tetris_wins_t* get_tetris_wins() {
  static Tetris_wins_t* views;
  if (views == NULL) {
    views = malloc(sizeof(Tetris_wins_t));
  }
  return views;
}
Game_wins_t* get_game_wins() {
  static Game_wins_t* game_wins;
  if (game_wins == NULL) {
    game_wins = malloc(sizeof(Game_wins_t));
    game_wins->title_win = newwin(3, 25, 1, 1);
    game_wins->menu_win = newwin(15, 25, 4, 1);
    game_wins->info_win = newwin(15, 25, 4, 26);
  }
  return game_wins;
}
void cleanup_game_wins(Game_wins_t* game_wins) {
  if (game_wins != NULL) {
    if (game_wins->title_win != NULL) {
      delwin(game_wins->title_win);
    }
    if (game_wins->menu_win != NULL) {
      delwin(game_wins->menu_win);
    }
    if (game_wins->info_win != NULL) {
      delwin(game_wins->info_win);
    }

    free(game_wins);
  }
}
