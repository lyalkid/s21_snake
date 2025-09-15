/*
* @author Azamat G. 
* @date 13.09.2025.
* @details
*
*/

#include "Snake.h"
s21::Apple::Apple() {
    berry = {rand()%HEIGHT,rand()%WIDTH};
}

void s21::Apple::spawn_apple() {
    berry.x = rand()%WIDTH;
    berry.y = rand()%HEIGHT;
}

