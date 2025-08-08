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
    View views = init_view();

    init_view(views);
    int ch;
    int tick = 0;           // Счётчик времени
    int delay_ms = 500;     // Скорость падения фигуры (500 мс)
    int running = 1;
    while(running){

        set_view(&views);
        ch = getch();
        running = 0;
    }
    terminate_ncurses(&views);
    
    return 0;
}

