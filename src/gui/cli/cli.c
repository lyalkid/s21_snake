//
// Created by Azamat G. on 08.08.2025.
//
#include "cli.h"

// bool is_ncurses_on() {
//     static bool* data;
//     if (data == NULL) {
//         data = (bool*)(malloc(sizeof(bool)));
//     }
//     return data;
// }

void init_ncurses(View* views) {
 initscr();
 cbreak();
 noecho();
 int h = 0, w = 0;

 init_colors();
 getmaxyx(stdscr, h, w);
 nodelay(stdscr, TRUE);
 keypad(stdscr, TRUE);
 curs_set(0);

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

 refresh();
}

void draw() {
 // init ncurses

 // crate windows


}