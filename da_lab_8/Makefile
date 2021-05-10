CC=g++
FLAGS=-std=c++14 -pedantic -Wall -Wextra -O2
OUTPUT=laba8

all: src/laba8.cpp
	$(CC) $(FLAGS) src/laba8.cpp -o $(OUTPUT)
benchmark: tests/benchmark.cpp
	$(CC) $(FLAGS) tests/benchmark.cpp -o benchmark

clean:
	rm -f $(OUTPUT) src/*.o benchmark
