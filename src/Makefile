CC = gcc
CP = g++
CFLAGS = -c
#-Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11


CORE_TETRIS_DIR = brick_game
#CORE_SNAKE_DIR = brick_game
GUI_CLI_DIR = gui/cli
GUI_DESKTOP_DIR = gui/desktop
SRC_DIR = .
UTILS_DIR = utils 
BIN_DIR = bin
GCOV_DIR = gcov_report
OBJ_DIR = obj
DOCS_DIR = docs

TETRIS_SRC = $(wildcard $(CORE_TETRIS_DIR)/*.c )
#SNAKE_SRC = $(wildcard $(CORE_SNAKE_DIR)/*.c )
CLI_SRC = $(wildcard $(GUI_CLI_DIR)/*.c)
UTILS_SRC = $(wildcard utils/*.c)
MAIN_SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.cpp )

UNAME_S := Linux
ifeq ($(UNAME_S),Linux)
 	OPEN_CMD = firefox
	ADD_LIB =  -lm -lrt -lpthread -D_GNU_SOURCE -lncurses
	TEST_LIB = -lcheck -lsubunit -lm
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lncurses
	TEST_LIB = -lcheck
endif

all: clean style run_cli

install: style cli
	mkdir $(BIN_DIR)
	$(CC) $(OBJ_DIR)/*.o -o $(BIN_DIR)/brick_game_cli -lncurses

dvi:
	mkdir $(DOCS_DIR)
	doxygen Doxyfile

style:
	clang-format --style=Google -i $(TETRIS_SRC) $(MAIN_SRC)  $(CLI_SRC) $(UTILS_SRC)

style_test:
	clang-format --style=Google -n $(TETRIS_SRC) $(MAIN_SRC)  $(CLI_SRC) $(UTILS_SRC)

create_file:
	test -f highscore.txt || ( touch highscore.txt && echo 0 >> highscore.txt )

cli: create_file 
	mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $(ADD_LIB) main_cli.c $(TETRIS_SRC) $(CLI_SRC) $(UTILS_SRC)
	mv *.o $(OBJ_DIR)

run_cli:install
	$(BIN_DIR)/brick_game_cli

clean:
	rm -rf ./$(BIN_DIR) ./$(OBJ_DIR) *.out *.o *.log ./$(DOCS_DIR)