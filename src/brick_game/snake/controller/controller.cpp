/*
* @author Azamat G. 
* @date 20.09.2025.
* @details
*
*/
#include  "controller.h"

extern "C" {
#include  "../../utils/utilities.h"
}

namespace s21 {
    Controller::Controller(s21::Snake *snake) : paused(false), active(true), updated(false),win(false), model(snake) {
        info = init_empty_gameInfo(2);
        null_array(info.field, HEIGHT, WIDTH);
        timer = init_shift_timer();
        state = INIT;
        // model->update(info.field);
    }

    GameInfo_t Controller::get_game_info() {
        return info;
    }


    GameInfo_t Controller::updateCurrentState() {
        int size = model->score;
        null_array(info.field, HEIGHT, WIDTH);
        for (int i = 0; i < size; i++) {
            const int x = model->body[i].x;
            const int y = model->body[i].y;
            if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT)) {
                if (i == 0) {
                    info.field[y][x] = HEAD;
                } else info.field[y][x] = SNAKE;
            }
        }
        info.field[model->berry.y][model->berry.x] = BERRY;

        //check collision
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                const int x1 = model->body[i].x;
                const int y1 = model->body[i].y;
                const int x2 = model->body[j].x;
                const int y2 = model->body[j].y;
                if (x1 == x2 && y1 == y2) {
                    state = GAME_OVER;
                }
            }
        }
        info.score = model->score;
        if (info.score > info.high_score) {
            write_high_score(info.score, 2);
            info.high_score = info.score;
        }
        info.pause = !paused;
        info.level = 1;
        info.speed = 1;
        if (size == 200) {
            win = true;
            state = WON;
        }
        return info;
    }

    void Controller::userInput(UserAction_t action, bool hold) {
        switch (action) {
            case Start:

                paused = false;
                if (state == GAME_OVER || state == INIT || state == WON) {
                    active = true;
                    model->reset();
                }
                state = GAME;
                break;

            case Pause:
                paused = !paused;
                if (!paused) {state = GAME;}
                // state = PAUSE;
                break;

            case Terminate:
                active = false;
                break;
            case Left: model->changeDirection(Left);
                break;
            case Right: model->changeDirection(Right);
                break;
            case Up: model->changeDirection(Up);
                break;
            case Down: model->changeDirection(Down);
                break;
            case Action:
                updated = true;
                break;
            default: break;
        }
        if (state == GAME && (model->direction_changed || updated || timer.time_to_shift)) {
            model->update(info.field);
            model->direction_changed = false;
            timer.time_to_shift = false;
            updated = false;
            get_time(&timer.before);
        }


        if (hold) { hold = false; } else {
            hold = true;
        }
    }
}
