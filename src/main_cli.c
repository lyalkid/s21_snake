#include <stdio.h>
#include "gui/cli/cli.h"

/*!
    \brief Родительский класс, не несущий никакой смысловой нагрузки

    Данный класс имеет только одну простую цель: проиллюстрировать то,
    как Doxygen документирует наследование
*/
int main(){
    init_nc();
    // init ncurses
    Tetris_wins_t views = init_view();

    init_view(views);
    int ch;
    int tick = 0;           // Счётчик времени
    int delay_ms = 500;     // Скорость падения фигуры (500 мс)
    int running = 1;
    // set_tetris_wins(&views);
    int play = menu();


    while(running){

        // render main win
        // choose game
        // initialize game or quite
        ch = getch();
        running = 0;
    }
    terminate_ncurses(&views);
    
    return 0;
}

