/*
* @author Azamat G. 
* @date 21.09.2025.
* @details
*
*/
#include "controller/controller.h"
#include "model/Snake.h"


extern "C" {
#include "../../gui/cli/cli.h"
#include "../../gui/cli/tetris/frontend.h"
#include "../brick_game.h"
#include "../utils/timer.h"
}

using namespace s21;

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

void debug_info(UserAction_t action, Vec2 dir, Vec2 head, bool shift, Vec2 body[], int score) {
    mvprintw(0, 22, "action: %s", actionToString(action));
    mvprintw(1, 22, "dir:   ,   ");
    mvprintw(1, 22, "dir: %d, %d", dir.x, dir.y);
    mvprintw(2, 22, "head:   ,   ");
    mvprintw(2, 22, "head: %d, %d", head.x, head.y);
    if (shift) {
        mvprintw(3, 22, "time to shift!");
    } else {
        mvprintw(3, 22, "              ");
    }
    for (int i = 0; i < score; i++) {
        mvprintw(4 + i, 22, "body[%d]: %d, %d", i, body[i].x, body[i].y);
    }
}

void render_snake(WINDOW *win, int **field, int score, int h_score, int level) {
    werase(win);
    mvprintw(0,22, "score:    ");
    mvprintw(0,22, "score: %d", score);
    mvprintw(1,22, "h_score:    ");
    mvprintw(1,22, "h_score: %d", h_score);
    mvprintw(2,22, "level:    ");
    mvprintw(2,22, "level: %d", level);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int res = field[i][j];
            const char *ch;

            if (res == SNAKE)      ch = "[]";
            else if (res == HEAD)  ch = ":)";
            else if (res == BERRY) ch = "@ ";
            else                   ch = "  ";

            if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
                wattron(win, COLOR_PAIR(res));
                mvwprintw(win, i + 1, j * scale_field + 1, "%s", ch);
                wattroff(win, COLOR_PAIR(res));
            } else {
                mvwprintw(win, i + 1, j * scale_field + 1, "%s", ch);
            }
        }
    }

    box(win, 0, 0);
    wrefresh(win);
    refresh();
}



void draw_snake(WINDOW *win, GameInfo_t info, Snake_state state ) {
    switch (state) {
        case INIT:
            render_welcome(win);
            break;
        case GAME:
            render_snake(win, info.field, info.score, info.high_score, info.level);
            break;
        case PAUSE:
            render_pause(win);
            break;
        case GAME_OVER:
            render_game_over(win);
            break;
        case WON:
            render_celebration(win);
    }
}


int main() {
    init_nc();
    WINDOW *win = newwin(FIELD_Y, FIELD_X, 0, 0);
    Snake snake{};
    Controller controller(&snake);
    UserAction_t action;
    while (controller.get_active()) {
        if (controller.get_paused()) {
            while (controller.get_paused()) {
                action = getSignal(getch());
                if (action == Pause)controller.userInput(action, true);
            }
        }
        action = getSignal(getch());

        // debug_info(action, controller.get_model().getDirection(), controller.get_model().getHead(),
        //            controller.timer.time_to_shift, controller.get_model().getBody(), controller.get_model().getScore());

        controller.userInput(action, true);

        // if (controller.get_updated()) {
            draw_snake(win, controller.updateCurrentState(), controller.get_state());
        //     controller.set_updated();
        // }

        countTime(&controller.timer);

    }
    delwin(win);
    endwin();
    return 0;
}
