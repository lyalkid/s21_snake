CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

GCOV_FOLDER = gcov_report

BG = brick_game
TETRIS_SRC=$(wildcard $(BG)/tetris/src/*.c $(BG)/utils/*.c $(BG)/*.c)
T_CLI_SRC = $(wildcard  gui/cli/*.c gui/cli/tetris/*.c )
SNAKE_SRC = $(wildcard $(BG)/snake/*/*.cpp   )

TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
T_CLI_OBJ = $(T_CLI_SRC:.c=.o)
T_LIB = libtetris.a
T_CLI = libtcli.a
#all, install, uninstall, clean, dvi, dist, test
all:
	make clean
	mkdir build
	make install
	make main
	#./build/main

install: cli desktop
uninstall: clean


cli: tetris_cli snake_cli
tetris_cli: $(T_CLI) $(T_LIB)
	gcc $(CFLAGS)  gui/cli/tetris/main_tetris.c -L. libtetris.a libtcli.a -lncurses -lm -o build/t_cli

snake_cli:
	g++ $(CFLAGS) gui/cli/snake/main.cpp  $(SNAKE_SRC) -L. libtetris.a libtcli.a -lncurses -o build/s_cli
main:
	gcc $(CFLAGS) gui/cli/main_cli.c -L. libtcli.a -lncurses -o build/cli
desktop:
	mkdir tmp
	cd tmp && qmake ../gui/desktop/ && make
	mv tmp/desktop build/
	rm -rf tmp
	#mv qui/desktop/tmp/desktop build
DOCS_DIR = docs
clean:
	rm -rf $(TETRIS_OBJ) $(T_LIB) $(T_CLI_OBJ) $(DOCS_DIR) dist ./build ./tmp highscore_snake.txt highscore_tetris.txt $(GCOV_FOLDER) *.a


dvi:
	mkdir $(DOCS_DIR)
	doxygen Doxyfile


dist: all
	mkdir dist
	cp -r brick_game gui Makefile build dist/
	tar -czf BRICKGAME-2.0.tar.gz dist
	mv BRICKGAME-2.0.tar.gz dist

test:
	g++ $(CFLAGS) $(SNAKE_SRC)  $(TETRIS_SRC)  -lncurses  tests/test_snake_controller.cpp  -lgtest -lgtest_main  -lrt -lm -o test
	chmod +x ./test
	./test
	rm test

gcov_report:
	mkdir $(GCOV_FOLDER)
	g++ $(CFLAGS) tests/test_snake_controller.cpp $(SNAKE_SRC) $(TETRIS_SRC) --coverage -lgtest -lgtest_main -lrt -lm -o $(GCOV_FOLDER)/gcov_test
	chmod +x $(GCOV_FOLDER)/gcov_test
	$(GCOV_FOLDER)/gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external --ignore-errors mismatch -c -d .
	genhtml -o report/ gcov_test.info
	mv report gcov_test.info $(GCOV_FOLDER)
	$(OPEN_CMD) ./report/index.html
	rm -rf gcov*


style:
	clang-format --style=Google -i $(TETRIS_SRC) $(T_CLI_SRC) $(SNAKE_SRC) gui/cli/snake/main.cpp gui/cli/tetris/main_tetris.c gui/desktop/*.cpp gui/desktop/*.h

$(T_LIB): $(TETRIS_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(T_CLI): $(T_CLI_OBJ)
	$(AR) $(ARFLAGS) -lncurses $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
