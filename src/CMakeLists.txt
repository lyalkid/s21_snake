 cmake_minimum_required(VERSION 3.26)
 project(snake-tetris C CXX)

 set(CMAKE_C_STANDARD 11)

 set(CMAKE_CXX_STANDARD 17)
 add_definitions(-Ddebug_bro)
 add_executable(snake-tetris
         brick_game/tetris/src/TGM3Randomizer.c
         brick_game/tetris/src/field_mechanics.c
         brick_game/tetris/src/game_rules.c
         brick_game/tetris/src/game_state_management.c
         brick_game/tetris/src/tetramino.c
         brick_game/tetris/src/tetramino_movement.c
         brick_game/utils/utilities.c
         gui/cli/tetris/main_tetris.c
         brick_game/brick_game.c
         brick_game/utils/defines.h
         brick_game/utils/timer.h
         brick_game/utils/timer.c
         brick_game/tetris/src/game_api.c
         gui/cli/cli.c
         gui/cli/tetris/frontend.c
#         brick_game/snake/main.cpp
         brick_game/snake/controller/controller.cpp
         brick_game/snake/controller/controller.h
         brick_game/snake/model/Snake.cpp
         brick_game/snake/model/Snake.h

 )
 find_package(Qt6Widgets REQUIRED)
 target_link_libraries(snake-tetris m ncurses)


#
#cmake_minimum_required(VERSION 3.26)
#project(Tetris LANGUAGES C CXX)
#
#
#set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 17)
#
## Пути к подпроектам
#add_subdirectory(brick_game)
#add_subdirectory(gui/cli)
#add_subdirectory(gui/desktop)
#
#
## main_cli.c → отдельный бинарь
## в корневом CMakeLists.txt
#add_executable(main_cli main_cli.c
#
#)
#target_link_libraries(main_cli PRIVATE brick_game cli ncurses)
#
#add_executable(main_tetris main_tetris.c
#            brick_game/tetris/src/TGM3Randomizer.c
#            brick_game/tetris/src/field_mechanics.c
#            brick_game/tetris/src/game_rules.c
#            brick_game/tetris/src/game_state_management.c
##            brick_game/tetris/src/storage.c
#            brick_game/tetris/src/tetramino.c
#            brick_game/tetris/src/tetramino_movement.c
#            brick_game/utils/utilities.c
#            main_tetris.c
#            brick_game/brick_game.c
#            brick_game/utils/defines.h
#        brick_game/utils/timer.h
#        brick_game/utils/timer.c
#
#            gui/cli/cli.c
##                gui/cli/tetris/frontend.c
#)
#target_link_libraries(main_tetris PRIVATE  cli m ncurses)
#
