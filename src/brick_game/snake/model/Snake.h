/*
* @author Azamat G.
* @date 13.09.2025.
* @details
*
*/

#ifndef SNAKE_H
#define SNAKE_H

extern "C"
{
#include "../../brick_game.h"
#include "../../utils/defines.h"
}


#include  <stdlib.h>
#include  <vector>
namespace s21 {
    typedef struct {
        int x;
        int y;
    }Vec2;

    class Snake {
    public:
        friend class Controller;
        Snake();
        void reset();
        void changeDirection(UserAction_t action);
        void update(int **field);

        Vec2 getDirection(){return dir;}
        Vec2 getHead(){return head;}
        Vec2 *getBody(){return body;}
        int getScore(){return score;}
        ~Snake() = default;
    private:
        int width;
        int height;
        int score;
        Vec2 body[200];
        Vec2 head;
        Vec2 berry;
        Vec2 dir;
        bool direction_changed;
        void spawn_berry();
    };
}
#endif //SNAKE_H
