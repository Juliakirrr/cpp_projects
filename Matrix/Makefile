.PHONY: all s21_matrix_oop.a

CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lm
COV = --coverage
LIB = s21_matrix_oop.a
s21_matrix_cpp = s21_*.cpp
s21_matrix_o = s21_*.o
TESTS = s21_matrix_tests

ifeq ($(shell uname -s), Linux)
	TEST_FLAGS += -lsubunit
endif

all: $(LIB)

$(LIB):
	$(CC) $(s21_matrix_cpp) -c $(FLAGS)
	ar rc $(LIB) $(s21_matrix_o)
	ranlib $(LIB)

covered:
	$(CC) $(s21_matrix_cpp) -c $(FLAGS) $(COV)
	ar rc $(LIB) $(s21_matrix_o)
	ranlib $(LIB)

test: clean covered
	$(CC) matrix_tests/*.cpp -c $(FLAGS) $(COV)
	$(CC) -o $(TESTS) $(TESTS).o *_test.o $(LIB) $(COV) $(FLAGS) $(TEST_FLAGS) -lgcov -lgtest -pthread
	./$(TESTS)

gcov_report: test
	lcov -t "coverage" -o coverage.info -c -d .
	lcov --remove coverage.info '/usr/include/*' -o coverage.info
	genhtml -o report coverage.info
	xdg-open report/index.html

style:
	clang-format -style=google -i matrix_tests/*.cpp *.cpp *.h
	clang-format -style=google -n matrix_tests/*.cpp *.cpp *.h

mem: test
ifeq ($(shell uname -s), Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file="valgrind.txt" --tool=memcheck  --leak-check=full ./$(TESTS)
else
	leaks --atExit -- ./$(TESTS)
endif

clean:
	rm -rf $(TESTS) *.a *.o *.gcda *.gcno *.gcov *.info *.html report valgrind.txt

rebuild: clean all