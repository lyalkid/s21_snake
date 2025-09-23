/*
 * @author Azamat G.
 * @date 12.08.2025.
 * @details
 *
 */
#include "../inc/tetris.h"
#include  "../inc/tetramino_movement.h"


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
        data = (TetrisData_t *) malloc(sizeof(TetrisData_t));
        *data = init_empty_data();
    }
    return data;
}

TetrisData_t init_empty_data(void) {
    TetrisData_t data = {0};
    data.is_active = true;
    data.is_win = false;
    data.changed = false;
    data.current_action = NONE_ACTION;
    data.current_state = STATE_INITIALIZE;
    // data.prev_state = data.current_state;
    data.shift_timer = init_shift_timer();
    data.current_tetraMino = init_empty_tetraMino();
    data.current_game_info = init_empty_gameInfo(1);
    return data;
}

const char *stateToString(Tetris_state_t s) {
    switch (s) {
        case STATE_INITIALIZE:
            return "start    ";
        case STATE_SPAWN:
            return "spawn    ";
        case STATE_MOVEMENT:
            return "movement ";
        // case STATE_ATTACH:
        //     return "attaching";
        case STATE_SHIFT:
            return "shift    ";
        case STATE_PAUSE:
            return "pause    ";
        case STATE_GAME_OVER:
            return "game_over";
        case STATE_EXIT:
            return "exit     ";
        // case STATE_MAIN_MENU:
        //   return "main_menu";
        default:
            return "unknown  ";
    }
}

const char *actionToString(UserAction_t s) {
    switch (s) {
        case Start:
            return "start      ";
            break;
        case Pause:
            return "pause      ";
            break;
        case Terminate:
            return "terminate  ";
            break;
        case Left:
            return "left       ";
            break;
        case Right:
            return "right      ";
            break;
        case Up:
            return "up         ";
            break;
        case Down:
            return "down       ";
        case Action:
            return "action     ";
    }
    return "none_action";
}

void userInput(UserAction_t action, bool hold) {
    TetrisData_t *data = get_data();
    main_fsm(data, action);
    countTime(&data->shift_timer);
    if (hold)
        hold = true;
    else
        hold = false;
}

void main_fsm(TetrisData_t *data, UserAction_t action) {
    Tetramino *tetramino = &data->current_tetraMino;
    GameInfo_t *game_info = &data->current_game_info;
    int state = data->current_state;

    // =========================
    //  Обработка паузы
    // =========================
    if ((state == STATE_MOVEMENT || state == STATE_SHIFT) && action == Pause) {
        game_info->pause = true;
        state = STATE_PAUSE;
        get_time(&data->shift_timer.before);
    }

    // =========================
    //  FSM
    // =========================
    if (state == STATE_INITIALIZE) {
        if (action == Terminate) {
            finish_game(data);
        } else if (action == Start) {
            state = STATE_SPAWN;
        }

    } else if (state == STATE_SPAWN) {
        int status = spawn_figure(tetramino, game_info);
        is_game_over(&state, status);

    } else if (state == STATE_MOVEMENT && !game_info->pause) {
        if (action == Terminate) {
            finish_game(data);
        } else {
            int shift = MY_OK;
            if (isHorizontalMoveOrRotate(action) == MY_OK) {
                onMoving(action);
            } else if (action == Down) {
                if (figure_is_attaching(action, data) == ERROR)
                    state = STATE_SPAWN;
            }
            if (shift == MY_OK && data->shift_timer.time_to_shift) {
                state = STATE_SHIFT;
            }
        }

    } else if (state == STATE_SHIFT && !game_info->pause) {
        if (figure_is_attaching(Down, data) == ERROR) {
            state = STATE_SPAWN;
        } else {
            state = STATE_MOVEMENT;
            data->shift_timer.time_to_shift = false;
            get_time(&data->shift_timer.before);
        }

    } else if (state == STATE_PAUSE) {
        if (action == Start) {
            game_info->pause = false;
            state = STATE_MOVEMENT;  // возвращаемся к движению
        } else if (action == Terminate) {
            finish_game(data);
        }

    } else if (state == STATE_GAME_OVER) {
        if (action == Start) {
            reset_game(data);       // обнуляем все данные
            state = STATE_SPAWN;    // начинаем новую игру
        } else if (action == Terminate) {
            finish_game(data);      // окончательный выход
        }
    }

    // =========================
    //  Флаг "данные изменились"
    // =========================
    if ((state == STATE_MOVEMENT || state == STATE_SHIFT) && !game_info->pause) {
        data->changed = true;
    }

    data->current_state = state;
}


void attach_tetramino(TetrisData_t *data) {
    Tetramino *tetramino = &data->current_tetraMino;
    GameInfo_t *game_info = &data->current_game_info;
    // attaching
    mergeFigureIntoField(tetramino->tmp_current_figure_on_field,
                         game_info->field);

    game_mechanics(data);

    // spawn
    get_data()->current_state = STATE_SPAWN;
}


void finish_game(TetrisData_t *data) {
    if (data->current_state != STATE_GAME_OVER && !data->is_win)
        data->is_active = false;
     data->current_state=STATE_EXIT;
    reset_game(data);
}

void reset_game(TetrisData_t *data) {
    data->current_tetraMino = init_empty_tetraMino();
    data->current_game_info = init_empty_gameInfo(1);
}

void free_game(TetrisData_t *data) {
    data->current_state = STATE_EXIT;
    // free_array(data->current_game_info.field, HEIGHT);
    // free_array(data->current_game_info.next, NEXT_FIELD);
    // free_array(data->current_tetraMino.tmp_current_figure_on_field, HEIGHT);
}

void onMoving(UserAction_t action) {
    Tetramino *tetramino = &get_data()->current_tetraMino;
    GameInfo_t *game_info = &get_data()->current_game_info;
    if (canMoveTetramino(*tetramino, game_info->field, action) == MY_OK) {
        moveTetramino(tetramino, action);
        placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
    }
}

int figure_is_attaching(UserAction_t action, TetrisData_t *data) {
    Tetramino *tetramino = &data->current_tetraMino;
    GameInfo_t *game_info = &data->current_game_info;
    moveTetramino(tetramino, action);

    if (check_collision(*tetramino, game_info->field) == ERROR) {
        tetramino->center_y--;
        placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
        // attaching
        mergeFigureIntoField(tetramino->tmp_current_figure_on_field,
                             game_info->field);

        game_mechanics(data);

        // spawn
        get_data()->current_state = STATE_SPAWN;
        return ERROR;
    }
    placeTetraminoInArray(*tetramino, tetramino->tmp_current_figure_on_field);
    return MY_OK;
}

int spawn_figure(Tetramino *tetraMino, GameInfo_t *game_info) {
    int is_all_ok_val = MY_OK;
    next_tetramino(&tetraMino->r);
    placeTetraminoInArray(*tetraMino, tetraMino->tmp_current_figure_on_field);
    is_all_ok_val =
            canMergeFigures(game_info->field, tetraMino->tmp_current_figure_on_field);
    return is_all_ok_val;
}

void is_game_over(int *state, int status) {
    if (status == MY_OK) {
        *state = STATE_MOVEMENT;
    } else {
        *state = STATE_GAME_OVER;

        if (get_data()->current_game_info.score > get_data()->current_game_info.high_score)
            write_high_score(get_data()->current_game_info.score, 1);
    }
}

GameInfo_t updateCurrentState() { return (get_data()->current_game_info); }
