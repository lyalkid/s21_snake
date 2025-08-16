/*
 * @author Azamat G.
 * @date 14.08.2025.
 * @details
 *
 */
#include "render.h"

void render_tetris_game_win(WINDOW* win, int** field,
                            int** current_figure_on_field) {
  werase(win);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int res = field[i][j] + current_figure_on_field[i][j];
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