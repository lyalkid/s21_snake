#include <stdio.h>

#include "gui/cli/cli.h"

void start_game(int choice) {
  endwin();  // завершили текущую ncurses-сессию
  switch (choice) {
    case 1:
      system("./build/t_cli");
      init_nc();
      break;
    case 2:
       system("./build/s_cli");
      break;
    default:
      break;
  }
}

int main() {
  // init_game_data();
  int choice = 1;
  init_nc();
   get_game_wins();

  while (choice) {
    choice =
        handle_menu(get_game_wins());  // frontend, с него получаем сигнал, который выбрал
    // cleanup_game_wins();
    // пользователь
    if (choice) {
      start_game(choice);

    } else {
      break;
    }
  }
  terminate_ncurses(get_game_wins());
  printf("%d", choice);
  return EXIT_SUCCESS;
}
