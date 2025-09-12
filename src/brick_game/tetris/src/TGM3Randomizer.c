/*
 * @author Azamat G.
 * @date 12.08.2025.
 * @details
 *
 */

#include "../../utils/defines.h"
#include "../../utils/utilities.h"
#include "../game_api/game_api.h"
#include "../inc/tetris.h"
int piece_str_to_type(const char *piece) {
  if (strcmp(piece, "I") == 0) return I;
  if (strcmp(piece, "J") == 0) return J;
  if (strcmp(piece, "L") == 0) return L;
  if (strcmp(piece, "O") == 0) return O;
  if (strcmp(piece, "S") == 0) return S;
  if (strcmp(piece, "T") == 0) return T;
  if (strcmp(piece, "Z") == 0) return Z;
  return -1;
}

int contains(const char *arr[], int size, const char *value) {
  for (int i = 0; i < size; i++) {
    if (strcmp(arr[i], value) == 0) return 1;
  }
  return 0;
}

int index_of(const char *arr[], int size, const char *value) {
  for (int i = 0; i < size; i++) {
    if (strcmp(arr[i], value) == 0) return i;
  }
  return -1;
}

void init_randomizer(TGM3Randomizer *r) {
  const char *pieces[7] = {"I", "J", "L", "O", "S", "T", "Z"};
  memcpy(r->pieces, pieces, sizeof(pieces));

  for (int i = 0; i < 35; i++) {
    r->pool[i] = r->pieces[i % 7];
  }

  const char *firstOptions[4] = {"I", "J", "L", "T"};
  const char *firstPiece = firstOptions[rand() % 4];

  r->history[0] = "S";
  r->history[1] = "Z";
  r->history[2] = "S";
  r->history[3] = firstPiece;

  r->order[0] = firstPiece;
  r->order_size = 1;
  get_data()->current_tetraMino.type = piece_str_to_type(firstPiece);
  // get_tetramino_instance()->next_type = piece_str_to_type(next_piece(r));
}

const char *next_piece(TGM3Randomizer *r) {
  int roll, idx;
  const char *piece = NULL;

  for (roll = 0; roll < 6; roll++) {
    idx = rand() % 35;
    piece = r->pool[idx];

    if (!contains(r->history, 4, piece) || roll == 5) {
      break;
    }
    if (r->order_size > 0) {
      r->pool[idx] = r->order[0];
    }
  }

  int pos = index_of(r->order, r->order_size, piece);
  if (pos != -1) {
    for (int i = pos; i < r->order_size - 1; i++) {
      r->order[i] = r->order[i + 1];
    }
    r->order_size--;
  }

  r->order[r->order_size++] = piece;

  int indexInPool = index_of(r->pool, 35, piece);
  if (indexInPool != -1) {
    r->pool[indexInPool] = r->order[0];
  }

  for (int i = 0; i < 3; i++) {
    r->history[i] = r->history[i + 1];
  }
  r->history[3] = piece;

  return piece;
}
void next_tetramino(TGM3Randomizer *r) {
  Tetramino *tetramino = &get_data()->current_tetraMino;
  tetramino->type = tetramino->next_type;
  tetramino->rotate = COMPLETE;
  tetramino->center_x = 0;
  tetramino->center_y = 0;
  null_array(tetramino->tmp_current_figure_on_field, HEIGHT, WIDTH);
  generateTetraminoShape(tetramino->coordinates, tetramino->rotate,
                         tetramino->type);
  tetramino->next_type = piece_str_to_type(next_piece(r));
}