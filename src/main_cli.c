#include <stdio.h>

#include "gui/cli/cli.h"

int main() {
  init_nc();
  // init ncurses
  Game_wins_t *game_wins = get_game_wins();
  int running = 1;
  int play = menu();
  while (play && running) {
    switch (play) {
      case 1:
        // start tetris
        running = 0;
        break;
      case 2:
        // start snake
        running = 0;
        break;
      case 3:
        // start cars
        running = 0;
        break;
      default:
        running = 0;
        break;
    }
  }

  cleanup_game_wins(game_wins);
  terminate_ncurses();
  printf("%d", play);
  return 0;
}
