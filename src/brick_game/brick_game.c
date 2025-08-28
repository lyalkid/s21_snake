/*
* @author Azamat G. 
* @date 28.08.2025.
* @details
*
*/
#include "brick_game.h"
#include "utils/utilities.h"
#include "utils/defines.h"
GameInfo_t* get_game_info() {
    static GameInfo_t* game_info;
    if (game_info == NULL) {
        game_info = malloc(sizeof(GameInfo_t));
        *game_info = init_empty_gameInfo();
    }
    return game_info;
}
GameInfo_t init_empty_gameInfo() {
    GameInfo_t gameInfo = {0};
    gameInfo.score = 0;
    gameInfo.high_score = 0;
    gameInfo.level = 0;
    gameInfo.pause = 0;
    gameInfo.speed = 0;
    gameInfo.field = malloc_array(HEIGHT, WIDTH);
    gameInfo.next = malloc_array(NEXT_FIELD, NEXT_FIELD);
    return gameInfo;
}