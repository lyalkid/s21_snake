//
// Created by Azamat G. on 08.08.2025.
//

#ifndef GAME_API_H
#define GAME_API_H

#include <stdbool.h>
#include <stdlib.h>
#include "../../brick_game.h"
#include "../inc/tetramino_movement.h"
#include "../inc/Timer.h"
typedef enum {
    STATE_START,
    STATE_SPAWN,
    STATE_MOVEMENT ,
    STATE_ATTACH,
    STATE_SHIFT,
    STATE_PAUSE,
    STATE_GAME_OVER,
    STATE_EXIT
}Tetris_state;

/**
 * @brief Структура для хранения игровой информации
 * @field currenState - текущее состоянии
 * @field shift_timer - таймер для управления скоростью
 * @field current_tetraMino - текущая фигура
 * @field current_game_info - текущее состояние игры
 */
typedef struct {
    UserAction_t current_action;
    Tetris_state current_state;
    Shift_timer shift_timer;
    Tetramino current_tetraMino;
    GameInfo_t current_game_info;
}TetrisData_t;

TetrisData_t *get_data(void);
TetrisData_t init_empty_data(void);

const char* stateToString(Tetris_state s);
void fsm(void);
void reset_game();
void free_game() ;
Tetris_state* get_state() ;
void userInput(UserAction_t action, bool hold);
void onMoving(UserAction_t action);

void onStart(TetrisData_t* data);
int onDownMoving(UserAction_t action) ;
int onSpawn(Tetramino *tetraMino, GameInfo_t *game_info);
int onShifting(void);
GameInfo_t updateCurrentState();


#endif //GAME_API_H
