CFLAGS= g++ -Wall -Werror -Wextra -std=c++17
LFLAGS=-lcheck -lpthread -lsubunit -lm
FLAGS=-lgtest -lgtest_main -pthread
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
CEXE=test
FOR_LCOV = --ignore-errors mismatch
VALGRIND_FLAGS  = 	--log-file="valgrind.txt" --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full
OBJTESTSNAKE = tests/main_test_snake.cpp tests/test_snake.cpp 
NAMETESTSNAKE =-fprofile-arcs -ftest-coverage -o test_snake
OBJS = brick_game/snake/*.cpp
PROJECT_DIR = gui/desktop/final
PRO_FILE = final.pro

BUILD_DIR = build

TETRIS_EXE = tetris
SNAKE_EXE = snake


.PHONY: dist clean


all: snake tetris brick_gameD
install: tetris snake brick_gameD

tetris:
	@mkdir -p $(BUILD_DIR)
	${CFLAGS} gui/cli/tetris/main.c gui/cli/tetris/front.cpp brick_game/tetris/back.cpp -lncurses -o build/tetris
snake:
	@mkdir -p $(BUILD_DIR)
	${CFLAGS} gui/cli/snake/front.cpp brick_game/snake/snake.cpp -lncurses -o $(BUILD_DIR)/$(SNAKE_EXE)
brick_gameD:
	cd $(PROJECT_DIR) && qmake
	cd $(PROJECT_DIR) && make
	cd $(PROJECT_DIR) && make clean

uninstall:
	rm -rf build

clean:
	rm -rf *.a *.o *.gcno *.gcda test *.info s21_test report valgrind.txt tetris snake dist $(BUILD_DIR)
	rm -rf htmlmake doc

test: clean
	g++ $(OBJTESTSNAKE) $(OBJS) $(NAMETESTSNAKE) $(FLAGS)
	@./test_snake

gcov_report:clean test
	lcov -t "result" -o res.info --no-external $(FOR_LCOV) -c -d . 
	genhtml -o report res.info 
	open report/index.html
	rm -rf *.gcda *.gcno *.info test_snake
	

test_tetris: 
	${CFLAGS} tests/*.c brick_game/tetris/back.cpp  gui/cli/tetris/front.cpp -o s21_test -lncurses $(LFLAGS)
	./s21_test

gcov_report_tetris: clean
	${CFLAGS} tests/*.c brick_game/tetris/back.cpp gui/cli/tetris/front.cpp -o s21_test -lncurses $(LFLAGS) ${GCOV_FLAGS}
	./s21_test
	lcov -t "gcov_test" -o gcov_test.info -c -d .
	genhtml -o report gcov_test.info
	xdg-open report/index.html
	rm -rf *.gcda *.gcno *.info

valgrind: clean test
	valgrind $(VALGRIND_FLAGS) ./test_snake
	grep -n "ERROR SUMMARY" valgrind.txt

valgrind_tetris: clean test
	valgrind $(VALGRIND_FLAGS) ./s21_test
	grep -n "ERROR SUMMARY" valgrind.txt

dvi: clean
	open brick_game_doc.md

dist: install
	mkdir -p dist
	cp -r Makefile brick_game game_score gui tetris dist/
	tar -ckzvf dist/tetris$(shell date +%Y%m%d).tar.gz -C dist .
	cd dist && rm -rf Makefile 
clang: 
	clang-format -n tests/*.c tests/*.h  tests/*.cpp
	clang-format -n brick_game/tetris/*.cpp  
	clang-format -n brick_game/snake/*.cpp brick_game/snake/*.h 
	clang-format -n gui/cli/snake/*.cpp gui/cli/snake/*.h 
	clang-format -n gui/cli/tetris/*.cpp gui/cli/tetris/*.h gui/cli/tetris/*.c
	clang-format -n gui/desktop/final/*.h gui/desktop/final/*.cpp


 
	
