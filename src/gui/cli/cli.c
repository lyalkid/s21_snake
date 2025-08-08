//
// Created by Azamat G. on 08.08.2025.
//
#include "cli.h"

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
}

/**
 * @brief Двигает фигуру влево.
 */
View init_view() {
  View views = {0};
  getmaxyx(stdscr, views.yMax, views.xMax);
  delwin(views.game_win);
  return views;
}
void set_view(View* views) {
  int h = 0, w = 0;
  getmaxyx(stdscr, h, w);
  printf("%d, %d", h, w);
  views->game_win =
      newwin(FIELD_Y, FIELD_X, (h - FIELD_Y) / 2, (w - FIELD_X) / 2);
  views->info_win = newwin(INFO_Y - 2, INFO_X, 0 + (h - FIELD_Y) / 2,
                           FIELD_X + (w - FIELD_X) / 2);
  views->next_win = newwin(NEXT_Y + 2, NEXT_X, INFO_Y - 2 + (h - FIELD_Y) / 2,
                           FIELD_X + (w - FIELD_X) / 2);

  refresh();
  box(views->game_win, 0, 0);
  box(views->info_win, 0, 0);
  box(views->next_win, 0, 0);

  wrefresh(views->game_win);
  wrefresh(views->info_win);
  wrefresh(views->next_win);
  //
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

void terminate_ncurses(View* views) {
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран

  refresh();
  delwin(views->game_win);
  delwin(views->info_win);
  delwin(views->next_win);
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран

  refresh();
  endwin();
}