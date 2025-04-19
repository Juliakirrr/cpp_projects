CC=g++
COMPILE_FLAGS= -Wall -Werror -Wextra -std=c++17 -pedantic -Wshadow
OPTIMIZATION_FLAGS= -O2 -Wpessimizing-move -Wredundant-move
SANITIZER_FLAGS= -fsanitize=undefined,address
COVERAGE_DIR=coverage
VALGRIND=valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file="logfile.out"

VECTOR_TEST=tests/vector_test.cpp
VECTOR_HEADER=containers/sequence_containers/vector/s21_vector.h

LIST_TEST=tests/list_test.cpp
LIST_HEADER=containers/sequence_containers/list/s21_list.h

QUEUE_TEST=tests/queue_test.cpp
QUEUE_HEADER=containers/container_adaptors/queue/s21_queue.h

STACK_TEST=tests/stack_test.cpp
STACK_HEADER=containers/container_adaptors/stack/s21_stack.h

ARRAY_TEST=tests/array_test.cpp
ARRAY_HEADER=containers/sequence_containers/array/s21_array.h

MAP_TEST=tests/map_test.cpp
MAP_HEADER=containers/associative_containers/map/s21_map.h

SET_TEST=tests/set_test.cpp
SET_HEADER=containers/associative_containers/set/s21_set.h

MULTISET_TEST=tests/multiset_test.cpp
MULTISET_HEADER=containers/associative_containers/multiset/s21_multiset.h

.PHONY: all clean clear style style-check coverage coverage-vector coverage-list coverage-queue coverage-stack coverage-array

all: test 

test: vector-test list-test queue-test stack-test array-test map-test set-test multiset-test

vector-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(VECTOR_TEST) -lgtest -o vector-test.out
	./vector-test.out

list-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(LIST_TEST) -lgtest -o list-test.out
	./list-test.out

queue-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(QUEUE_TEST) -lgtest -o queue-test.out
	./queue-test.out

stack-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(STACK_TEST) -lgtest -o stack-test.out
	./stack-test.out

array-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(ARRAY_TEST) -lgtest -o array-test.out
	./array-test.out


map-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(MAP_TEST) -lgtest -o map-test.out
	./map-test.out

multiset-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(MULTISET_TEST) -lgtest -o multiset-test.out
	./multiset-test.out

set-test:
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) $(SET_TEST) -lgtest -o set-test.out
	./set-test.out

coverage: coverage-vector coverage-list coverage-queue coverage-stack coverage-array coverage-set coverage-map coverage-multiset

coverage-vector:
	@mkdir -p $(COVERAGE_DIR)/vector
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(VECTOR_TEST) -lgtest -o vector-test.out
	./vector-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/vector.info --include "$(VECTOR_HEADER)"
	genhtml $(COVERAGE_DIR)/vector.info --output-directory $(COVERAGE_DIR)/vector

coverage-list:
	@mkdir -p $(COVERAGE_DIR)/list
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(LIST_TEST) -lgtest -o list-test.out
	./list-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/list.info --include "$(LIST_HEADER)"
	genhtml $(COVERAGE_DIR)/list.info --output-directory $(COVERAGE_DIR)/list

coverage-queue:
	@mkdir -p $(COVERAGE_DIR)/queue
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(QUEUE_TEST) -lgtest -o queue-test.out
	./queue-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/queue.info --include "$(QUEUE_HEADER)"
	genhtml $(COVERAGE_DIR)/queue.info --output-directory $(COVERAGE_DIR)/queue

coverage-stack:
	@mkdir -p $(COVERAGE_DIR)/stack
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(STACK_TEST) -lgtest -o stack-test.out
	./stack-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/stack.info --include "$(STACK_HEADER)"
	genhtml $(COVERAGE_DIR)/stack.info --output-directory $(COVERAGE_DIR)/stack

coverage-array:
	@mkdir -p $(COVERAGE_DIR)/array
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(ARRAY_TEST) -lgtest -o array-test.out
	./array-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/array.info --include "$(ARRAY_HEADER)"
	genhtml $(COVERAGE_DIR)/array.info --output-directory $(COVERAGE_DIR)/array


coverage-set:
	@mkdir -p $(COVERAGE_DIR)/set
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(SET_TEST) -lgtest -o set-test.out
	./set-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/set.info --include "$(SET_HEADER)"
	genhtml $(COVERAGE_DIR)/set.info --output-directory $(COVERAGE_DIR)/set


coverage-multiset:
	@mkdir -p $(COVERAGE_DIR)/multiset
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(MULTISET_TEST) -lgtest -o multiset-test.out
	./multiset-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/multiset.info --include "$(MULTISET_HEADER)"
	genhtml $(COVERAGE_DIR)/multiset.info --output-directory $(COVERAGE_DIR)/multiset


coverage-map:
	@mkdir -p $(COVERAGE_DIR)/map
	$(CC) -g $(SANITIZER_FLAGS) $(COMPILE_FLAGS) --coverage $(MAP_TEST) -lgtest -o map-test.out
	./map-test.out
	lcov --rc branch_coverage=1 --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,inconsistent \
		--capture --directory . --output-file $(COVERAGE_DIR)/map.info --include "$(MAP_HEADER)"
	genhtml $(COVERAGE_DIR)/map.info --output-directory $(COVERAGE_DIR)/map

style-check:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -n -verbose -Werror --style=Google

style:
	find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i -verbose --style=Google

clean: clear
clear:
	rm -rf *.out *.gcda *.gcno *.info $(COVERAGE_DIR)
