CC=g++
FLAGS=-std=c++14 -pedantic -Wall -Wextra -O2
OBJECTS = src/kp.o src/lz77/lz77.o src/lz77/sufftree/tree.o
OUTPUT=kp

$(OUTPUT): $(OBJECTS)
	$(CC) $(FLAGS) -o $(OUTPUT) $(OBJECTS)

src/kp.o: src/kp.cpp src/lz77/lz77.o 
src/lz77/lz77.o: src/lz77/lz77.cpp src/lz77/lz77.hpp src/lz77/sufftree/tree.o
src/lz77/sufftree/tree.o: src/lz77/sufftree/tree.cpp src/lz77/sufftree/tree.hpp

clean:
	rm -f $(OUTPUT) $(OBJECTS)


