/*
* @author Azamat G. 
* @date 20.09.2025.
* @details
*
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <unistd.h>

extern "C" {
#include "../../brick_game.h"
#include "../../utils/timer.h"
}

#include  "../model/Snake.h"
#define BERRY 1
#define HEAD 2
#define SNAKE 3

typedef enum {
    INIT = 0,
    GAME,
    PAUSE,
    GAME_OVER,
    WON
} Snake_state;

namespace s21 {
    /**
     *@param bool paused ;
     *@param bool active ;
     *@param GameInfo_t info;
     *@param Snake* model;
     */
    class Controller {
    public:
        Controller();

        ~Controller() = default;

        bool get_active() { return active; }
        bool get_paused() { return paused; }
        bool get_updated() { return updated; }
        void set_updated() { updated = false; }
        Snake_state get_state() {
            if (paused) return PAUSE;
            return state;
        }
        Snake get_model() { return *model; }

        GameInfo_t get_game_info();

        void userInput(UserAction_t action, bool hold);

        GameInfo_t updateCurrentState();

    private:
        bool paused;
        bool active;
        bool updated;
        bool win;
        Snake_state state;
        GameInfo_t info{};
        Snake *model;

    public:
        Shift_timer timer{};
    };
}
#endif //CONTROLLER_H
