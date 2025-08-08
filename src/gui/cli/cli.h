//
// Created by Azamat G. on 08.08.2025.
//


#ifndef CLI_H
#define CLI_H
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#define HEIGHT 20
#define WIDTH 10
#define scale_field 2
#define scale 2

#define FIELD_Y HEIGHT + 2
#define FIELD_X WIDTH* scale_field + 2

#define NEXT_FIELD 10
#define INFO_FIELD 10

#define INFO_X INFO_FIELD* scale + 2
#define INFO_Y INFO_FIELD + 2

#define NEXT_X NEXT_FIELD* scale + 2
#define NEXT_Y NEXT_FIELD

typedef struct {
    int yMax;
    int xMax;
#ifndef debug
    WINDOW* game_win;
    WINDOW* info_win;
    WINDOW* next_win;
    #endif
} View;

/*!
    \brief Родительский класс, не несущий никакой смысловой нагрузки

    Данный класс имеет только одну простую цель: проиллюстрировать то,
    как Doxygen документирует наследование
*/
void init_nc();
void set_view(View* views);
View init_view();
void init_colors();
void terminate_ncurses(View* views);

#endif //CLI_H
