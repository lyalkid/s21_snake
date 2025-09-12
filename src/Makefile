CC = gcc
CP = g++
WFLAGS = #-Wall -Werror -Wextra  -Wunused-function
CFLAGS = -c -std=c11 $(WFLAGS)
LDFLAGS = -std=c11 $(WFLAGS) -fprofile-arcs -ftest-coverage

BRICK_GAME = brick_game
CORE_TETRIS_DIR = $(BRICK_GAME)/tetris
GUI_CLI_DIR = gui/cli
GAME_API = $(CORE_TETRIS_DIR)/game_api
UTILS = $(BRICK_GAME)/utils

HEADERS = $(wildcard $(CORE_TETRIS_DIR)/inc/*.h $(CORE_TETRIS_DIR)/*.h $(BRICK_GAME)/*.h $(UTILS)/*.h )
BRICK_GAME_SRC = $(wildcard $(BRICK_GAME)/*.c)
TETRIS_SRC = $(wildcard  $(CORE_TETRIS_DIR)/src/*.c )
CLI_SRC = $(wildcard $(GUI_CLI_DIR)/*.c $(GUI_CLI_DIR)/*/*.c)
MAIN_SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.cpp )
GAME_API_SRC = $(wildcard $(GAME_API)/*.c)
UTILS_SRC = $(wildcard $(UTILS)/*.c)


SRC_DIR = .
BIN_DIR = bin
GCOV_DIR = gcov_report
OBJ_DIR = obj

DOCS_DIR = docs
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
all: clean style run_tetis

install: style cli
	$(CC) $(OBJ_DIR)/*.o -o $(BIN_DIR)/brick_game_cli -lncurses

dvi:
	mkdir $(DOCS_DIR)
	doxygen Doxyfile

style:
	@clang-format --style=Google -i $(TETRIS_SRC) *.c  $(CLI_SRC) $(HEADERS)  $(TETRIS_SRC) $(CLI_SRC) $(UTILS_SRC) $(BRICK_GAME_SRC) $(GAME_API_SRC)

style_test:
	@clang-format --style=Google -n $(TETRIS_SRC) $(MAIN_SRC)  $(CLI_SRC) $(HEADERS)

create_file:
	@test -f highscore.txt || ( touch highscore.txt && echo 0 >> highscore.txt )

cli: create_file tetris

	$(CC) $(CFLAGS) $(ADD_LIB) main_cli.c  $(GUI_CLI_DIR)/*.c
	$(CC) *.o -o $(BIN_DIR)/main_cli -lncurses
	@mv *.o $(OBJ_DIR)

tetris:
	mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $(ADD_LIB) main_tetris.c $(TETRIS_SRC) $(CLI_SRC) $(UTILS_SRC) $(BRICK_GAME_SRC) $(GAME_API_SRC)
	mv *.o $(OBJ_DIR)
	mkdir $(BIN_DIR)
	$(CC) $(OBJ_DIR)/*.o -o $(BIN_DIR)/t_cli -lncurses -lm




run_tetis:clean  tetris
	$(CC) $(OBJ_DIR)/*.o -o $(BIN_DIR)/brick_game_cli -lncurses -lm
	$(BIN_DIR)/brick_game_cli


clean:
	rm -rf ./$(BIN_DIR) ./$(OBJ_DIR) *.out *.o  ./$(DOCS_DIR)

