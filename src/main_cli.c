
#include <stdio.h>

#include "brick_game/brick_game.h"
#include "game_api/game_api.h"

int main() {
  // init_game_data();
  int choice = 1;
  init_nc();
  get_game_wins();
  while (choice) {
    choice = handle_menu();  // frontend, с него получаем сигнал, который выбрал
    // пользователь
    if (choice) {
      clear();
      start_game(choice);
    } else {
      break;
    }
  }

  terminate_ncurses();
  printf("%d", choice);
  return EXIT_SUCCESS;
}
