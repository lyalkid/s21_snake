//
// Created by Azamat G. on 08.08.2025.
//

#ifndef GAME_API_H
#define GAME_API_H
#include <stdbool.h>
#include <stdlib.h>
#include "../../brick_game.h"
#include "../inc/tetramino_movement.h"

typedef enum {
    start,
    spawn,
    movement ,
    attaching,
    shift,
    pause,
    game_over
}State;


typedef struct {
    State state;
    GameInfo_t game_info;
    Tetramino tetramino;
}TetrisData_t;
const char* stateToString(State s);
void fsm(UserAction_t action);
State* get_state() ;
void userInput(UserAction_t action, bool hold);
void onMoving(UserAction_t action);

int onDownMoving(UserAction_t action) ;
int onSpawn(Tetramino tetraMino, GameInfo_t game_info);
int onShifting(void);
GameInfo_t updateCurrentState();


#endif //GAME_API_H
