/*
 * @author Azamat G.
 * @date 09.08.2025.
 * @details
 *
 */

#include <curses.h>

#include "cli.h"

int handle_menu() {
  const char* list[ITEMS] = {"exit", "tetris", "snake", "cars"};

  init_menu();
  int highlight = 0;
  int choice = 0;
  int c = 0;
  while (1) {
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
  WINDOW* title_win = get_game_wins()->title_win;
  WINDOW* menu_win = get_game_wins()->menu_win;
  WINDOW* info_win = get_game_wins()->info_win;
  keypad(menu_win, TRUE);
  set_title(title_win, "BRICKGAME");
  refresh();
  box(menu_win, 0, 0);
  box(title_win, 0, 0);
  box(info_win, 0, 0);
  wrefresh(menu_win);
  wrefresh(title_win);
  wrefresh(info_win);
}

void set_title(WINDOW* title_win, char* title) {
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
