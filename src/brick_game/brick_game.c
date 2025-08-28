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


UserAction_t getSignal(int user_input) {
    UserAction_t sig = NONE_ACTION;
    if (user_input == 'f') {
        sig = Up;
    } else if (user_input == 119) {
        sig = Action;
    } else if (user_input == 115) {
        sig = Down;
    } else if (user_input == 97) {
        sig = Left;
    } else if (user_input == 100) {
        sig = Right;
    } else if (user_input == ESCAPE || user_input == 'q' || user_input == 'Q') {
        sig = Terminate;
    } else if (user_input == 'n' || user_input == 'N') {
        sig = Start;
    } else if (user_input == SPACE || user_input == 'p' || user_input == 'P') {
        sig = Pause;
    }
    return sig;
}
