/*
 * @author Azamat G.
 * @date 14.08.2025.
 * @details
 *
 */
#include "../inc/tetris.h"

Tetramino init_empty_tetraMino() {
  Tetramino tetraMino = (Tetramino){0};
  tetraMino.type = 0;
  tetraMino.next_type = 0;

  tetraMino.rotate = 0;
  tetraMino.center_x = 0;
  tetraMino.center_y = 0;
  for (int i = 0; i < 8; i++) {
    tetraMino.coordinates[i] = 0;
  }

  tetraMino.tmp_current_figure_on_field = malloc_array(HEIGHT, WIDTH);

  return tetraMino;
}
void placeTetraminoInArray(Tetramino tetraMino, int** next) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      next[i][j] = 0;
    }
  }
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMino.coordinates[i] + tetraMino.center_x;
    int y = tetraMino.coordinates[i + 1] + tetraMino.center_y;
    next[y][x] = tetraMino.type;
  }
}
void setCoordinates(int* coordinates, const int* values) {
  for (int i = 0; i < 8; i++) {
    coordinates[i] = values[i];
  }
}
void generateTetraminoShape(int coordinates[], int rotate, int type) {
  if (type >= T && type <= L) {
    generateShapeTJL(coordinates, rotate, type);
  } else if (type >= I && type <= Z) {
    generateShapeSZorI(coordinates, rotate, type);
  } else if (type == O) {
    int coord[] = {4, 0, 5, 0, 4, 1, 5, 1};
    setCoordinates(coordinates, coord);
  } else {
    int coord[] = {0, 0, 0, 0, 0, 0, 0, 0};
    setCoordinates(coordinates, coord);
  }
}

void generateShapeSZorI(int coordinates[], int rotate, int type) {
  if (rotate % 2 == 1 && type == Z) {
    int coord[] = {4, 2, 4, 1, 5, 1, 5, 0};
    setCoordinates(coordinates, coord);

    /* ..#
     * .##
     * .#.
     *
     * */
  } else if (type == Z) {
    int coord[] = {3, 0, 4, 0, 4, 1, 5, 1};
    setCoordinates(coordinates, coord);

    /* ...
     * ##.
     * .##
     *
     * */
  } else if (rotate % 2 == 1 && type == S) {
    int coord[] = {4, 0, 4, 1, 5, 1, 5, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .##
     * ..#
     *
     * */

  } else if (type == S) {
    int coord[] = {4, 0, 5, 0, 3, 1, 4, 1};
    setCoordinates(coordinates, coord);

    /* ...
     * .##
     * ##.
     *
     * */

  } else if (rotate % 2 == 1 && type == I) {
    int coord[] = {5, 2, 5, 1, 5, 0, 5, 3};
    setCoordinates(coordinates, coord);

    /* ..#.
     * ..#.
     * ..#.
     * ..#.
     *
     * */
  } else if (type == I) {
    int coord[] = {3, 0, 4, 0, 5, 0, 6, 0};
    setCoordinates(coordinates, coord);

    /* ....
     * ....
     * ####
     * ....
     *
     * */
  }
}
void generateShapeTJL(int coordinates[], int rotate, int type) {
  // TODO если это Т то поднять наверх

  // TODO ПРОВЕРИТЬ на коректность в соответвии со специф tetris rotate system
  if (type == T && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 4, 2};
    setCoordinates(coordinates, coord);

    /* ...
     * ###
     * .#.
     *
     * */
  } else if (type == T && rotate == RIGHT) {
    int coord[] = {3, 1, 4, 1, 4, 0, 4, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * ##.
     * .#.
     *
     * */

  } else if (type == T && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 4, 0};

    setCoordinates(coordinates, coord);

    /* .#.
     * ###
     * ...
     *
     * */
  } else if (type == T && rotate == REFLEX) {
    int coord[] = {5, 1, 4, 1, 4, 0, 4, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .##
     * .#.
     *
     * */
  }

  else if (type == L && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 5, 0};
    setCoordinates(coordinates, coord);
    /* ..#
     * ###
     * ...
     *
     * */

  } else if (type == L && rotate == RIGHT) {
    int coord[] = {4, 0, 4, 1, 4, 2, 5, 2};
    setCoordinates(coordinates, coord);
    /* .#.
     * .#.
     * .##
     *
     * */

  } else if (type == L && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 3, 2};
    setCoordinates(coordinates, coord);
    /*
     * ...
     * ###
     * #..
     *
     * */

  } else if (type == L && rotate == REFLEX) {
    int coord[] = {4, 0, 4, 1, 4, 2, 3, 0};
    setCoordinates(coordinates, coord);
    /* ##.
     * .#.
     * .#.
     *
     * */

  } else if (type == J && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 3, 0};
    setCoordinates(coordinates, coord);
    /*
     * #..
     * ###
     * ...
     *
     * */

  } else if (type == J && rotate == RIGHT) {
    int coord[] = {4, 0, 4, 1, 4, 2, 5, 0};
    setCoordinates(coordinates, coord);

    /* .##
     * .#.
     * .#.
     *
     * */
  } else if (type == J && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 5, 2};
    setCoordinates(coordinates, coord);
    /*
     * ...
     * ###
     * ..#
     *
     * */

  } else if (type == J && rotate == REFLEX) {
    int coord[] = {4, 0, 4, 1, 4, 2, 3, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .#.
     * ##.
     *
     * */
  }
}

void spawnNextTetramino(Tetramino* tetraMino) {
  // int current = tetraMino->type;
  // int next = tetraMino->next_type;

  // if (current == 0) {
  //   current = tetraMino->type = get_random(7);
  //   tetraMino->next_type = get_random(7);

  // } else {
  //   int tmp = 1;
  //   int flag = 1;
  //   while (flag) {
  //     //      printw("\nfdfdfdfdf");
  //     tmp = get_random(get_real_len_of_number(tetraMino->meshok.pieses, 7));
  //     int tmp_q = tetraMino->meshok.pieses[tmp - 1];
  //     if (tmp_q != 0) {
  //       tetraMino->next_type = tetraMino->meshok.pieses[tmp - 1];
  //       current = tetraMino->type = next;
  //       flag = 0;
  //       break;
  //     }
  //   }
  // }
  tetraMino->rotate = COMPLETE;
  tetraMino->center_x = 0;
  tetraMino->center_y = 0;
  null_array(tetraMino->tmp_current_figure_on_field, HEIGHT, WIDTH);
  generateTetraminoShape(tetraMino->coordinates, tetraMino->rotate,
                         tetraMino->type);
}