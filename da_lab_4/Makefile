CC=g++
CFLAGS=-std=c++14 -pedantic -Wall -Wextra
OUTPUT=laba4

all: src/main.cpp src/aho_corasick.o
	$(CC) $(CFLAGS) src/main.cpp src/aho_corasick.o -o $(OUTPUT)
src/aho_corasick.o: src/aho_corasick.cpp src/aho_corasick.hpp
	$(CC) $(CFLAGS) -c src/aho_corasick.cpp -o src/aho_corasick.o

benchmark: tests/benchmark.cpp src/aho_corasick.o
	$(CC) $(CFLAGS) tests/benchmark.cpp src/aho_corasick.o -o benchmark

clean:
	rm -f **/*.o $(OUTPUT) benchmark
