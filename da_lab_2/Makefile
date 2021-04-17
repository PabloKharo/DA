CC=g++
CFLAGS=-std=c++14 -pedantic -Wall -Wextra -pg
OUTPUT=laba2

all: src/main.cpp src/tree.o src/sltree.o src/tree.hpp
	$(CC) $(CFLAGS) src/main.cpp src/tree.o src/sltree.o -o $(OUTPUT)
src/tree.o: src/tree.cpp src/tree.hpp
	$(CC) $(CFLAGS) -c src/tree.cpp -o src/tree.o
src/sltree.o: src/sltree.cpp src/tree.hpp
	$(CC) $(CFLAGS) -c src/sltree.cpp -o src/sltree.o

benchmark: src/tree.o src/sltree.o src/tree.hpp tests/benchmark.cpp
	$(CC) $(CFLAGS) tests/benchmark.cpp src/tree.o src/sltree.o -o benchmark

clean:
	rm -f **/*.o $(OUTPUT) benchmark
