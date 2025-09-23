CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Ibrick_game/tetris/inc -Ibrick_game/utils
AR = ar
ARFLAGS = rcs

BG = brick_game
TETRIS_SRC=$(wildcard $(BG)/tetris/*/*.c $(BG)/utils/*.c $(BG)/*.c)
T_CLI_SRC = $(wildcard  gui/cli/*.c gui/cli/tetris/*.c )
SNAKE_SRC = $(wildcard $(BG)/snake/*/*.cpp gui/cli/snake/main.cpp  )

TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
T_CLI_OBJ = $(T_CLI_SRC:.c=.o)
T_LIB = libtetris.a
T_CLI = libtcli.a

all:
	make clean
	mkdir build
	make install
	make main
	#./build/main


main:
	gcc main_cli.c -L. libtcli.a -lncurses -o build/cli

install: cli desktop

cli: tetris_cli snake_cli

desktop:
	mkdir tmp
	cd tmp && qmake ../gui/desktop/ && make
	mv tmp/desktop build/
	rm -rf tmp
	#mv qui/desktop/tmp/desktop build

tetris_cli: $(T_CLI) $(T_LIB)
	gcc main_tetris.c -L. libtetris.a libtcli.a -lncurses -lm -o build/t_cli

snake_cli:
	g++  $(SNAKE_SRC) -L. libtetris.a libtcli.a -lncurses -o build/s_cli

style:
	clang-format --style=Google -i $(TETRIS_SRC) $(T_CLI_SRC) $(SNAKE_SRC)

$(T_LIB): $(TETRIS_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(T_CLI): $(T_CLI_OBJ)
	$(AR) $(ARFLAGS) -lncurses $@ $^




%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TETRIS_OBJ) $(T_LIB) $(T_CLI_OBJ) $(T_CLI) ./build ./tmp highscore_snake.txt highscore_tetris.txt

.PHONY: all clean
