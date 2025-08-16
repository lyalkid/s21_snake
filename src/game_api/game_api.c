/*
* @author Azamat G. 
* @date 12.08.2025.
* @details
*
*/
#include "game_api.h"

void selectGame( GameType game) {
    GameType* currentGame = getCurrentGameType();
    *currentGame = game;
}

void userInput(UserAction_t action, bool hold) {
    const GameType* currentGame = getCurrentGameType();
    if (*currentGame == GAME_TETRIS) tetris_userInput(action, hold);
    // else if (*currentGame == GAME_SNAKE) snake_userInput(action, hold);
}

GameInfo_t updateCurrentState() {
    const GameType* currentGame = getCurrentGameType();
    if (*currentGame == GAME_TETRIS) return tetris_updateCurrentState();
    // else return snake_updateCurrentState();
}




void tetris_userInput(UserAction_t action, bool hold){}

GameInfo_t tetris_updateCurrentState(){}