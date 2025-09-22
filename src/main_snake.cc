#include  <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "brick_game/snake/model/Snake.h"

typedef struct {
    int x;
    int y;
}
vec2;

int main() {
    int screen_width = 10, screen_height = 20;
    WINDOW *win = initscr();
    keypad(win, TRUE);
    nodelay(win, TRUE);
    curs_set(0);
    // box(win, 0, 0);

    vec2 segments[200];
    vec2 head = {0, 0};
    vec2 dir = {1, 0};
    vec2 berry = {rand() % screen_width, rand() % screen_height};
    int score = 1;

    while (true) {
        int pressed = wgetch(win);
        if (pressed == KEY_LEFT) {
            if (dir.x == 1) continue;
            dir.x = -1;
            dir.y = 0;
        }
        if (pressed == KEY_RIGHT) {
            if (dir.x == -1) continue;
            dir.x = +1;
            dir.y = 0;
        }
        if (pressed == KEY_DOWN) {
            if (dir.y == -1)continue;
            dir.x = 0;
            dir.y = +1;
        }
        if (pressed == KEY_UP) {
            if (dir.y == 1) continue;
            dir.x = 0;
            dir.y = -1;
        }
        if (pressed == '\e') {
            break;
        }

        for (int i = score; i > 0; i--) {
            segments[i] = segments[i - 1];
        }
        segments[0] = head;

        head.x += dir.x;
        head.y += dir.y;
        if (head.x > screen_width * 2) head.x = head.x % screen_width;
        if (head.x < 0) head.x = head.x + screen_width * 2;
        if (head.y > screen_height * 2) head.y = head.y % screen_height;
        if (head.y < 0) head.y = head.y + screen_height * 2;


        if (head.x == berry.x && head.y == berry.y) {
            score++;
            berry.x = rand() % screen_width;
            berry.y = rand() % screen_height;
        }
        //----draw----
        werase(win);
        mvaddch(berry.y, berry.x * 2, '@');
        for (int i = 0; i < score; i++) {
            if (i == 0) {
                mvaddch(segments[i].y, segments[i].x * 2, '+');
            } else {
                mvaddch(segments[i].y, segments[i].x * 2, 'o');
            }
        }
        box(win, 0, 0);
        usleep(125000);
    }
    endwin();
    return 0;
}
