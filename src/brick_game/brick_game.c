/*
 * @author Azamat G.
 * @date 28.08.2025.
 * @details
 *
 */
#include "brick_game.h"

#include "utils/defines.h"
#include "utils/utilities.h"
// GameInfo_t* get_game_info_instance() {
//   static GameInfo_t* game_info;
//   if (game_info == NULL) {
//     game_info = malloc(sizeof(GameInfo_t));
//     game_info->score = 0;
//     game_info->high_score = 0;
//     game_info->level = 1;
//     game_info->pause = 0;
//     game_info->speed = 0;
//     game_info->field = malloc_array(HEIGHT, WIDTH);
//     game_info->next = malloc_array(NEXT_FIELD, NEXT_FIELD);
//   }
//   return game_info;
// }

GameInfo_t init_empty_gameInfo(void) {
  GameInfo_t gameInfo;
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
  } else if (user_input == 'w') {
    sig = Action;
  } else if (user_input == 's') {
    sig = Down;
  } else if (user_input == 'a') {
    sig = Left;
  } else if (user_input == 'd') {
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
