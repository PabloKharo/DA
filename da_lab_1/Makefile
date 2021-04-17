CC=g++
CFLAGS=-std=c++14 -pedantic -Wall -Wextra -Wno-unused-variable 
OUTPUT=solution

all: src/sort.o src/md5.o src/main.cpp src/vector.hpp src/pair.hpp
	$(CC) $(CFLAGS) src/md5.o src/sort.o src/main.cpp -o $(OUTPUT)
src/sort.o: src/sort.cpp src/sort.hpp src/vector.hpp src/pair.hpp src/md5.o
	$(CC) $(CFLAGS) -c sort.cpp
src/md5.o: src/md5.cpp src/md5.hpp 
	$(CC) $(CFLAGS) -c src/md5.cpp

benchmark: src/sort.o src/md5.o tests/benchmark.cpp src/vector.hpp src/pair.hpp
	$(CC) $(CFLAGS) src/md5.o src/sort.o src/benchmark.cpp -o benchmark
	
clean:
	rm -f *.o $(OUTPUT) benchmark
