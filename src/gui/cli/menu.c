/*
 * @author Azamat G.
 * @date 09.08.2025.
 * @details
 *
 */

#include <curses.h>

#include "cli.h"
Game_wins_t* get_game_wins() {
  static Game_wins_t* game_wins;
  if (game_wins == NULL) {
    game_wins = malloc(sizeof(Game_wins_t));
  }
  return game_wins;
}

int menu() {
  const char* list[ITEMS] = {"tetris", "snake", "cars", "exit"};
  char item[20];
  WINDOW* title_win = get_game_wins()->title_win;
  WINDOW* menu_win = get_game_wins()->menu_win;
  WINDOW* info_win = get_game_wins()->info_win;
  title_win = newwin(3, 25, 1, 1);
  menu_win = newwin(15, 25, 4, 1);
  keypad(menu_win, TRUE);

  mvwprintw(title_win, 1, 8, "BRICKGAME");
  refresh();
  box(menu_win, 0, 0);
  box(title_win, 0, 0);
  wrefresh(menu_win);
  wrefresh(title_win);
  int highlight = 0;
  int choice = 0;
  int c = 0;
  while (1) {
    print_menu(menu_win, highlight, list);
    c = wgetch(menu_win);
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
    // timeout(1000000);
  }
  return 0;
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