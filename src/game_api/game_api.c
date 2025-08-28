/*
* @author Azamat G. 
* @date 12.08.2025.
* @details
*
*/
#include "game_api.h"






void start_game(int choice) {
    switch (choice) {
        case 1:
            system("./build/azamat_tetris");
            break;
        case 2:

            break;
        default:
            break;
    }
}


GameData_t* get_instanse() {
    static GameData_t* instance;
    if (instance == NULL) {
        instance = (GameData_t *) malloc(sizeof(GameData_t));
    }
    return instance;
}




