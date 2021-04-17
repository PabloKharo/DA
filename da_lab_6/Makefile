CC=g++
FLAGS=-std=c++14 -pedantic -Wall -Wextra -O2
OUTPUT=laba6

all: src/laba6.cpp src/long_num.o
	$(CC) $(FLAGS) src/laba6.cpp src/long_num.o -o $(OUTPUT)

src/long_num.o: src/long_num.hpp src/long_num.cpp
	$(CC) $(FLAGS) -c src/long_num.cpp -o src/long_num.o
	
benchmark: tests/benchmark.cpp src/long_num.o
	$(CC) $(FLAGS) tests/benchmark.cpp src/long_num.o -o benchmark -lgmp -lgmpxx

clean:
	rm -f $(OUTPUT) $(TEST_OUTPUT) benchmark src/*.o
