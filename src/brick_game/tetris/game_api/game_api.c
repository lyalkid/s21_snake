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
TetrisData_t *get_data(void) {
  static TetrisData_t *data;
  if (data == NULL) {
    data = (TetrisData_t *)malloc(sizeof(TetrisData_t));
    *data = init_empty_data();
  }
  return data;
}

TetrisData_t init_empty_data(void) {
  TetrisData_t data = {0};
  data.current_action = NONE_ACTION;
  data.current_state = STATE_START;
  data.shift_timer = init_shift_timer();
  data.current_tetraMino = init_empty_tetraMino();
  data.current_game_info = init_empty_gameInfo();
  return data;
}

Tetris_state *get_state() {
  static Tetris_state *state;
  if (state == NULL) {
    state = malloc(sizeof(Tetris_state));
  }
  return state;
}

const char *stateToString(Tetris_state s) {
  switch (s) {
    case STATE_START:
      return "start    ";
    case STATE_SPAWN:
      return "spawn    ";
    case STATE_MOVEMENT:
      return "movement ";
    case STATE_ATTACH:
      return "attaching";
    case STATE_SHIFT:
      return "shift    ";
    case STATE_PAUSE:
      return "pause    ";
    case STATE_GAME_OVER:
      return "game_over";
    case STATE_EXIT:
      return "exit     ";
    default:
      return "unknown  ";
  }
}

void userInput(UserAction_t action, bool hold) {
  TetrisData_t *data = get_data();

  switch (action) {
    case Start:
      break;
    case Pause:
      data->current_game_info.pause = 1;
      break;
    case Terminate:
      data->current_state = STATE_EXIT;
      fsm();
      break;
    // case Up:
    // break;
    case Left:
    case Right:
    case Down:
    case Action:
      fsm();
      data->current_action = NONE_ACTION;
      break;
  }

  if (hold) {
    hold = true;
  } else {
    hold = false;
  }
}

void fsm() {
  TetrisData_t *data = get_data();

  int is_game_over = MY_OK;
  switch (data->current_state) {
    case STATE_START:
      if (data->current_game_info.field != NULL &&
          data->current_tetraMino.tmp_current_figure_on_field != NULL) {
        reset_game();
      }
      data->current_state = STATE_SPAWN;
      // data->current_action = NONE_ACTION;
      break;
    case STATE_SPAWN:
      is_game_over =
          onSpawn(&data->current_tetraMino, &data->current_game_info);
      if (!is_game_over) {
        data->current_state = STATE_GAME_OVER;
      } else {
        // spawn figure
        data->current_state = STATE_MOVEMENT;
      }
      break;
    case STATE_MOVEMENT:
      int shift = MY_OK;
      if (isHorizontalMoveOrRotate(data->current_action) == MY_OK) {
        onMoving(data->current_action);
      } else if (isDownMove(data->current_action)) {
        shift = onDownMoving(data->current_action);
      }
      // else if (data->current_action == Pause) {
      //     data->currentState = STATE_PAUSE;
      // }
      if (shift == MY_OK && data->shift_timer.time_to_shift == true) {
        data->current_state = STATE_SHIFT;
      }
      break;

    case STATE_SHIFT:
      data->current_action = Down;
      onDownMoving(data->current_action);
      data->shift_timer.time_to_shift = false;
      get_time(&data->shift_timer.before);

      if (data->current_state != STATE_SPAWN) {
        data->current_state = STATE_MOVEMENT;
      }
      data->current_action = NONE_ACTION;
      break;
    case STATE_PAUSE:

      break;

    case STATE_GAME_OVER:
      break;
    case STATE_EXIT:
      data->current_action = Terminate;
      free_game();
      exit(EXIT_SUCCESS);
      break;
      // case movement:
      //     if (isHorizontalMoveOrRotate(current_action) == MY_OK) {
      //         onMoving(current_action);
      //     } else if (isDownMove(current_action)) {
      //         onDownMoving(current_action);
      //     }
      //     break;
      // case shift:
      //     if (timer->time_to_shift == true) {
      //         onDownMoving(Down);
      //         timer->time_to_shift = false;
      //         get_time(&timer->before, NULL);
      //     }
      //     break;
      //
      //
      //
      // case pause:
      //     while (getch() != 'p') {
      //         timeout(10);
      //     }
      //     *state = start;
      //     break;
      // case game_over:
      //     while (getch() != 'p') {
      //         timeout(1000);
      //     }
      //     break;
      // default:
      //     break;
      //     *state = shift;
  }
}

void reset_game() {
  TetrisData_t *data = get_data();
  *data = init_empty_data();
}

void free_game() {
  TetrisData_t *data = get_data();
  data->current_state = STATE_EXIT;
  free_array(data->current_game_info.field, HEIGHT);
  free_array(data->current_game_info.next, NEXT_FIELD);
  free_array(data->current_tetraMino.tmp_current_figure_on_field, HEIGHT);

  // free(data);
}

void onMoving(UserAction_t action) {
  Tetramino *tetramino = &get_data()->current_tetraMino;
  GameInfo_t *game_info = &get_data()->current_game_info;
  if (canMoveTetramino(*tetramino, game_info->field, action) == MY_OK) {
    moveTetramino(tetramino, action);
    placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
  }
}

int onDownMoving(UserAction_t action) {
  Tetramino *tetramino = &get_data()->current_tetraMino;
  GameInfo_t *game_info = &get_data()->current_game_info;
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
    get_data()->shift_timer.delay_to_shift = (long)game_info->speed;
    // spawn

    get_data()->current_state = STATE_SPAWN;
    // next_tetramino(&tetramino->r);
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

int onSpawn(Tetramino *tetraMino, GameInfo_t *game_info) {
  int is_all_ok_val = MY_OK;

  next_tetramino(&tetraMino->r);

  placeTetraminoInArray(*tetraMino, tetraMino->tmp_current_figure_on_field);

  is_all_ok_val =
      canMergeFigures(game_info->field, tetraMino->tmp_current_figure_on_field);

  return is_all_ok_val;
}

GameInfo_t updateCurrentState() {
  fsm();
  return (get_data()->current_game_info);
}

// void fsm(UserAction_t action) {
//     State *state = get_state();
//     switch (*state) {
//         case shift:
//             if (timer->time_to_shift == true) {
//                 onDownMoving(Down);
//                 timer->time_to_shift = false;
//                 get_time(&timer->before, NULL);
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
