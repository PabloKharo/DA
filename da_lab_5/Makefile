CC=g++
FLAGS=-std=c++14 -pedantic -Wall -Wextra -O2
OUTPUT=laba5

all: src/laba5.cpp src/tree.o
	$(CC) $(FLAGS) src/laba5.cpp src/tree.o -o $(OUTPUT)

src/tree.o: src/tree.hpp src/tree.cpp
	$(CC) $(FLAGS) -c src/tree.cpp -o src/tree.o

benchmark: src/tree.o tests/benchmark.cpp
	$(CC) $(FLAGS) tests/benchmark.cpp src/tree.o -o benchmark

clean:
	rm -f $(OUTPUT) src/*.o benchmark
