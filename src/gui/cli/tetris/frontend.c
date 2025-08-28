/*
 * @author Azamat G.
 * @date 18.08.2025.
 * @details
 *
 */

#include "frontend.h"

#include "../cli.h"

void draw_tetris(GameInfo_t currentState) {
     Tetris_wins_t *t_wins = get_tetris_wins();
    render_game_win(t_wins->game_win, currentState.field, currentState.next);
}

void render_game_win(WINDOW* win, int** field, int** next) {
  werase(win);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int res = field[i][j] + next[i][j];
      if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
        wattron(win, COLOR_PAIR(res));

        mvwprintw(win, i + 1, j * scale_field + 1, "  ");

        wattroff(win, COLOR_PAIR(res));

      } else {
        mvwprintw(win, i + 1, j * scale_field + 1, "[]");
      }
    }
  }

  box(win, 0, 0);
  wrefresh(win);
  refresh();
}
//
// void render_next_win(WINDOW* next_win, int type) {
//   werase(next_win);
//
//   mvwprintw(next_win, 1, 4 * 2, "NEXT");
//   mvwprintw(next_win, 2, 3 * 2, "TETRAMINO:");
//
//   int coordinates[8] = {};
//   get_TetraMino(coordinates, COMPLETE, type);
//
//   for (int i = 0; i < 8; i += 2) {
//     int x = coordinates[i];
//     int y = coordinates[i + 1] + 5;
//     if (x < 1 || x > NEXT_X || y > NEXT_Y || y < 1) {
//       mvwprintw(next_win, 1, 1, "smth wrong\n x:%d\n y:%d\n", x, y);
//       //      break;
//     } else {
//       wattron(next_win, COLOR_PAIR(type));
//       mvwprintw(next_win, y, x * 2 + 1, "  ");
//       wattroff(next_win, COLOR_PAIR(type));
//     }
//   }
//
//   box(next_win, 0, 0);
//   wrefresh(next_win);
//   refresh();
// }
// void render_info_win(WINDOW* info_win, int h_score, int score, int level,
//                      int count[]) {
//   werase(info_win);
//
//   int stat_w = 7 * 2, stat_h = 1;
//   wattron(info_win, COLOR_PAIR(4));
//   mvwprintw(info_win, 1, 2, "high_score:");
//   mvwprintw(info_win, 2, 2, "%d", h_score > score ? h_score : score);
//   wattroff(info_win, COLOR_PAIR(4));
//   wattron(info_win, COLOR_PAIR(6));
//
//   mvwprintw(info_win, 4, 2, "score:");
//   mvwprintw(info_win, 5, 2, "%d", score);
//   wattroff(info_win, COLOR_PAIR(6));
//   wattron(info_win, COLOR_PAIR(7));
//
//   mvwprintw(info_win, 7, 2, "level:");
//
//   mvwprintw(info_win, 8, 2, "%d", level);
//   wattroff(info_win, COLOR_PAIR(7));
//
//   mvwprintw(info_win, stat_h, stat_w, "STATS:");
//   for (int i = 0; i < 7; i++) {
//     mvwprintw(info_win, stat_h + i + 1, stat_w, "%c:%d", piece(i + 1),
//               count[i]);
//   }
//   box(info_win, 0, 0);
//   wrefresh(info_win);
//   refresh();
// }
//
// char piece(int type) {
//   char r = '0';
//   switch (type) {
//     case T:
//       r = 'T';
//       break;
//
//     case O:
//       r = 'O';
//       break;
//
//     case S:
//       r = 'S';
//       break;
//
//     case Z:
//       r = 'Z';
//       break;
//
//     case L:
//       r = 'L';
//       break;
//
//     case J:
//       r = 'J';
//       break;
//     case I:
//       r = 'I';
//       break;
//   }
//   return r;
// }


// void init_ncurses(Tetris_wins_t* t_wins) {
//   initscr();
//   cbreak();
//   noecho();
//   int h = 0, w = 0;
//
//   init_colors();
//   getmaxyx(stdscr, h, w);
//   nodelay(stdscr, TRUE);
//   keypad(stdscr, TRUE);
//   curs_set(0);
//
//   t_wins->game_win =
//       newwin(FIELD_Y, FIELD_X, (h - FIELD_Y) / 2, (w - FIELD_X) / 2);
//   t_wins->info_win = newwin(INFO_Y - 2, INFO_X, 0 + (h - FIELD_Y) / 2,
//                             FIELD_X + (w - FIELD_X) / 2);
//   t_wins->next_win = newwin(NEXT_Y + 2, NEXT_X, INFO_Y - 2 + (h - FIELD_Y) / 2,
//                             FIELD_X + (w - FIELD_X) / 2);
//
//   refresh();
//   box(t_wins->game_win, 0, 0);
//   box(t_wins->info_win, 0, 0);
//   box(t_wins->next_win, 0, 0);
//
//   wrefresh(t_wins->game_win);
//   wrefresh(t_wins->info_win);
//   wrefresh(t_wins->next_win);
//
//   refresh();
// }

// void init_colors() {
//   start_color();
//   init_pair(9, COLOR_BLACK, COLOR_BLACK);
//   init_pair(1, COLOR_BLACK, COLOR_RED);
//   init_pair(2, COLOR_BLACK, COLOR_CYAN);
//   init_pair(3, COLOR_BLACK, COLOR_BLUE);
//   init_pair(4, COLOR_BLACK, COLOR_YELLOW);
//   init_pair(5, COLOR_BLACK, COLOR_WHITE);
//   init_pair(6, COLOR_BLACK, COLOR_GREEN);
//   init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
// }

// void terminate_ncurses(Tetris_wins_t* t_wins) {
//   clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
//   clear();  // Очищаем экран
//
//   refresh();
//   delwin(t_wins->game_win);
//   delwin(t_wins->info_win);
//   delwin(t_wins->next_win);
//   clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
//   clear();  // Очищаем экран
//
//   refresh();
//   endwin();
// }

// void print_main_menu(WINDOW* main_menu_win) {
//   werase(main_menu_win);
//   mvwprintw(main_menu_win, 1, WIDTH / 2, "HELLO ");
//   mvwprintw(main_menu_win, HEIGHT / 2 + 1, 1, "W,A,S,D - to move");
//   mvwprintw(main_menu_win, HEIGHT / 2 + 2, 1, "G - PAUSE");
//   mvwprintw(main_menu_win, HEIGHT / 2 + 3, 1,
//             "Q or ESCAPE -\n exit session/game ");
//   mvwprintw(main_menu_win, HEIGHT / 2 + 5, 1,
//             "N or ENTER - \n start/resume game ");
//
//   box(main_menu_win, 0, 0);
//   wrefresh(main_menu_win);
//   refresh();
// }

// void game_over(WINDOW* game_win) {
//   werase(game_win);
//   mvwprintw(game_win, HEIGHT / 2, WIDTH / 2, "IT's");
//   mvwprintw(game_win, HEIGHT / 2 + 1, WIDTH / 2, "GAME OVER");
//
//   box(game_win, 0, 0);
//   wrefresh(game_win);
//   refresh();
// }

// void render_pause(WINDOW* game_win) {
//   werase(game_win);
//   mvwprintw(game_win, HEIGHT / 2, WIDTH / 2, "PAUSE ");
//   box(game_win, 0, 0);
//   wrefresh(game_win);
//   refresh();
// }
