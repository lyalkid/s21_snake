cmake_minimum_required(VERSION 3.26)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_definitions(-Ddebug_bro)
add_executable(tetris
        main_cli.c
        gui/cli/cli.c
        gui/cli/cli.h
        brick_game/brick_game.h
        brick_game/tetris_engine.c
        brick_game/tetris_engine.h

)
target_link_libraries(tetris m ncurses)