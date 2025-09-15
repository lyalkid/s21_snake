cmake_minimum_required(VERSION 3.26)
add_library(brick_game STATIC
        brick_game.c
        utils/utilities.c
        tetris/src/TGM3Randomizer.c
        tetris/src/timer.c
        tetris/src/field_mechanics.c
        tetris/src/game_rules.c
        tetris/src/game_state_management.c
        tetris/src/storage.c
        tetris/src/tetramino.c
        tetris/src/tetramino_movement.c
        snake/Snake.cpp
        snake/Snake.h
        snake/Apple.cpp
)
target_include_directories(brick_game PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/tetris/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/tetris/game_api
)