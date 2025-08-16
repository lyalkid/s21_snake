//
// Created by Azamat G. on 08.08.2025.
//

#ifndef GAME_API_H
#define GAME_API_H
#include <stdbool.h>
#include <stdlib.h>
#include "../brick_game/brick_game.h"



void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void tetris_userInput(UserAction_t action, bool hold);

GameInfo_t tetris_updateCurrentState();

typedef enum { GAME_TETRIS, GAME_SNAKE } GameType;

GameType *getCurrentGameType() {
    static GameType *currentGame;
    if (currentGame == NULL) { currentGame = (GameType *) malloc(sizeof(GameType)); }
    return currentGame;
}
void selectGame( GameType game);

#endif //GAME_API_H
