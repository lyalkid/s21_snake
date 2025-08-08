//
// Created by Azamat G. on 08.08.2025.
//

#ifndef GAME_API_H
#define GAME_API_H
#include <stdbool.h>


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

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();


#endif //GAME_API_H
