CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Ibrick_game/tetris/inc -Ibrick_game/utils
AR = ar
ARFLAGS = rcs

BG = brick_game
TETRIS_SRC=$(wildcard $(BG)/tetris/*/*.c $(BG)/utils/*.c $(BG)/*.c)
T_CLI_SRC = $(wildcard  gui/cli/*.c gui/cli/tetris/*.c )


TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
T_CLI_OBJ = $(T_CLI_SRC:.c=.o)
T_LIB = libtetris.a
T_CLI = libtcli.a

all: $(T_LIB) main
	gcc main_tetris.c -L. libtetris.a libtcli.a -lncurses -lm -o t
	./main

main:$(T_CLI)
	gcc main_cli.c -L. libtcli.a -lncurses -o main

style:
	clang-format --style=Google -i $(TETRIS_SRC) $(T_CLI_SRC)

$(T_LIB): $(TETRIS_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(T_CLI): $(T_CLI_OBJ)
	$(AR) $(ARFLAGS) -lncurses $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TETRIS_OBJ) $(T_LIB) $(T_CLI_OBJ) $(T_CLI)

.PHONY: all clean
