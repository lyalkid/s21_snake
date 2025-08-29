/*
 * @author Azamat G.
 * @date 12.08.2025.
 * @details
 *
 */
#include "game_api.h"

#include "../inc/Timer.h"

// typedef enum {
//     Start,
//     Pause,
//     Terminate,
//     Left, movement
//     Right, movement
//     Up, movement
//     Down, movement
//     Action, movement
//   } UserAction_t;
State *get_state() {
  static State *state;
  if (state == NULL) {
    state = malloc(sizeof(State));
  }
  return state;
}
const char *stateToString(State s) {
  switch (s) {
    case start:
      return "start";
    case spawn:
      return "spawn";
    case movement:
      return "movement";
    case attaching:
      return "attaching";
    case shift:
      return "shift";
    case pause:
      return "pause";
    case game_over:
      return "game_over";
    default:
      return "unknown";
  }
}

void userInput(UserAction_t action, bool hold) {
  State *state = get_state();
  switch (action) {
    case Start:
      *state = start;
      break;
    case Pause:
      *state = pause;
      break;
    case Terminate:
      break;
    case Down:
    case Action:
    case Left:

    case Right:
      *state = movement;
      break;
    default:
      *state = shift;
      break;
  }

  if (hold) {
    hold = true;
  } else
    hold = false;
}

void onMoving(UserAction_t action) {
  Tetramino *tetramino = get_tetramino_instance();
  GameInfo_t *game_info = get_game_info_instance();
  if (canMoveTetramino(*tetramino, game_info->field, action) == MY_OK) {
    moveTetramino(tetramino, action);
    placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
  }
}

int onDownMoving(UserAction_t action) {
  Tetramino *tetramino = get_tetramino_instance();
  GameInfo_t *game_info = get_game_info_instance();
  moveTetramino(tetramino, action);
  if (check_collision(*tetramino, game_info->field) == ERROR) {
    tetramino->center_y--;
    // attaching
    placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
    mergeFigureIntoField(tetramino->tmp_current_figure_on_field,
                         game_info->field);

    // calc score
    game_info->score +=
        calc_score(removeFullLines(game_info->field, HEIGHT, WIDTH));
    game_info->level = game_info->score / 600;
    game_info->speed = TIME * pow(0.9, game_info->level);
    get_shift_timer_instance()->delay_to_shift = (suseconds_t)game_info->speed;
    // spawn

    next_tetramino(&tetramino->r);
    // int is_all_ok_val = onSpawn(*tetramino, *game_info);

    // if (is_all_ok_val!= MY_OK) {
    //     State *state = get_state();
    //      *state = game_over;
    //
    // }

    return ERROR;
  }

  placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
  return MY_OK;
}

int onSpawn(Tetramino tetraMino, GameInfo_t game_info) {
  int is_all_ok_val = MY_OK;

  next_tetramino(&tetraMino.r);

  placeTetraminoInArray(tetraMino, tetraMino.tmp_current_figure_on_field);

  is_all_ok_val =
      canMergeFigures(game_info.field, tetraMino.tmp_current_figure_on_field);

  return is_all_ok_val;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *game_info = get_game_info_instance();
  return *game_info;
}

// void fsm(UserAction_t action) {
//     State *state = get_state();
//     switch (*state) {
//         case shift:
//             if (timer->time_to_shift == true) {
//                 onDownMoving(Down);
//                 timer->time_to_shift = false;
//                 gettimeofday(&timer->before, NULL);
//             }
//             break;
//         case movement:
//             if (isHorizontalMoveOrRotate(action) == MY_OK) {
//                 onMoving(action);
//             } else if (isDownMove(action)) {
//                 onDownMoving(action);
//             }
//             break;
//         case pause:
//             break;
//         case game_over:
//             break;
//         default:
//             break;
//             *state = shift;
//     }
//
//
//     if (*state == attaching) {
//         *state = shift;
//     }
//     if (*state == shift) {
//
//     }
// }
