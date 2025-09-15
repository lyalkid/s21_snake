/*
* @author Azamat G.
* @date 13.09.2025.
* @details
*
*/

#ifndef SNAKE_H
#define SNAKE_H
#include "../utils/defines.h"
#include  <stdlib.h>

namespace s21 {
    typedef struct {
        int x;
        int y;
    } vec2;

    class Snake {
    public:
        Snake();
        ~Snake();


    private:
        int size;
        vec2 head{};
        vec2 direction{};
        vec2 segments[HEIGHT * WIDTH]{};
    };

    class Apple {
    public:
        Apple();
        ~Apple();

    private:
        vec2 berry{};
        void spawn_apple();
    };
}
#endif //SNAKE_H
