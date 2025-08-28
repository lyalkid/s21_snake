//
// Created by Azamat G. on 08.08.2025.
//

#ifndef GAME_API_H
#define GAME_API_H
#include <stdbool.h>
#include <stdlib.h>
#include "../brick_game/brick_game.h"
#include "../gui/cli/cli.h"
typedef enum {
    STATE_START,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAMEOVER,
    STATE_EXIT
} GameState_t;
typedef struct {
    GameState_t state;
    GameInfo_t gameInfo;
}GameData_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void start_game(int gameType );
GameData_t* get_instanse() ;

#endif //GAME_API_H
