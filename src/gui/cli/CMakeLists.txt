cmake_minimum_required(VERSION 3.26)


add_library(cli STATIC
        cli.c
        tetris/frontend.c
)

target_include_directories(cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tetris
)

target_link_libraries(cli PUBLIC brick_game ncurses)
