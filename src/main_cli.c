
#include <stdio.h>

#include "brick_game/brick_game.h"
#include "gui/cli/cli.h"


int main() {
  init_nc();
  // init ncurses
  Game_wins_t *game_wins = get_game_wins();
  int choice = 1;
  while (choice) {
    choice = handle_menu();
    if (choice) start_game(&choice);
    else break;
  }
  cleanup_game_wins(game_wins);
  terminate_ncurses();
  printf("%d", choice);
  return EXIT_SUCCESS;
}
int main() { return 0; }
