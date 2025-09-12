//
// Created by Azamat G. on 08.08.2025.
//
#include "cli.h"

#include "../../brick_game/utils/defines.h"
#include "../../brick_game/utils/utilities.h"
// #include <curses.h>
#include <stdio.h>
void init_nc() {
  initscr();
  cbreak();
  noecho();
  //  int h = 0, w = 0;

  init_colors();

  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(0);

  // инициализация игровых окон
}

/**
 * @brief Двигает фигуру влево.
 */
Tetris_wins_t init_tetris_wins() {
  Tetris_wins_t t_wins = {};
  getmaxyx(stdscr, t_wins.yMax, t_wins.xMax);
  // delwin(t_wins.game_win);
  return t_wins;
}
void set_tetris_wins(Tetris_wins_t* t_wins) {
  t_wins->game_win = newwin(FIELD_Y, FIELD_X, 0, 0);
  t_wins->info_win = newwin(INFO_Y - 2, INFO_X, 0, FIELD_X);
  t_wins->next_win = newwin(NEXT_Y + 2, NEXT_X, INFO_Y - 2, FIELD_X);
  refresh();
  box(t_wins->game_win, 0, 0);
  box(t_wins->info_win, 0, 0);
  box(t_wins->next_win, 0, 0);
  wrefresh(t_wins->game_win);
  wrefresh(t_wins->info_win);
  wrefresh(t_wins->next_win);
  refresh();
}

void init_colors() {
  start_color();
  init_pair(11, COLOR_RED, COLOR_BLACK);
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
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
  cleanup_game_wins();
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран
  refresh();
  refresh();
  endwin();
}

Tetris_wins_t* get_tetris_wins() {
  static Tetris_wins_t* t_wins;
  if (t_wins == NULL) {
    t_wins = malloc(sizeof(Tetris_wins_t));
    t_wins->xMax = 0;
    t_wins->yMax = 0;
  }
  return t_wins;
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
void cleanup_game_wins() {
  Game_wins_t* game_wins = get_game_wins();
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

int handle_menu() {
  const char* list[ITEMS] = {"exit", "tetris", "snake"};

  init_menu();
  int highlight = 0;
  int choice = 0;
  int c = 0;
  while (1) {
    timeout(100000);
    print_menu(get_game_wins()->menu_win, highlight, list);
    c = wgetch(get_game_wins()->menu_win);
    if (c == KEY_UP || c == CONTROL_UP) {
      highlight--;
      if (highlight < 0) highlight = ITEMS - 1;
    } else if (c == KEY_DOWN || c == CONTROL_DOWN) {
      highlight++;
      if (highlight >= ITEMS) highlight = 0;

    } else if (c == CONTROL_NEXT) {
      choice = highlight;
    } else {
      refresh();
    }
    // Если сделан выбор (Enter)
    if (c == CONTROL_NEXT) {
      break;
    }
  }
  return choice;
}

void init_menu() {
  curs_set(0);
  WINDOW* title_win = get_game_wins()->title_win;
  WINDOW* menu_win = get_game_wins()->menu_win;
  WINDOW* info_win = get_game_wins()->info_win;
  keypad(menu_win, TRUE);
  set_title(title_win, "BRICKGAME");
  // refresh();
  box(menu_win, 0, 0);
  box(title_win, 0, 0);
  box(info_win, 0, 0);
  wrefresh(menu_win);
  wrefresh(title_win);
  wrefresh(info_win);
}

void set_title(WINDOW* title_win, char* title) {
  werase(title_win);
  mvwprintw(title_win, 1, 8, "%s", title);
}

void print_menu(WINDOW* menu_win, int highlight, const char** choices) {
  int x = 2, y = 2;
  box(menu_win, 0, 0);

  for (int i = 0; i < ITEMS; ++i) {
    if (highlight == i) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    y++;
  }
  wrefresh(menu_win);
}
