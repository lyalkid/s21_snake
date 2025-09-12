//
// Created by Azamat G. on 08.08.2025.
//

#ifndef BRICK_GAME_H
#define BRICK_GAME_H

// #define None_action 8
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

// void userInput(UserAction_t action, bool hold) {
//   // else if (*currentGame == GAME_SNAKE) snake_userInput(action, hold);
// }
//
// GameInfo_t updateCurrentState() {
//   // else return snake_updateCurrentState();
// }

// GameInfo_t* get_game_info_instance();

GameInfo_t init_empty_gameInfo(void);
UserAction_t getSignal(int user_input);
#endif  // BRICK_GAME_H
