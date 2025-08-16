//
// Created by Azamat G. on 08.08.2025.
//

#ifndef BRICK_GAME_H
#define BRICK_GAME_H
#include <stdlib.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
} UserAction_t;

typedef struct {
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int** field;
  int** next;
} GameInfo_t;

#endif  // BRICK_GAME_H
