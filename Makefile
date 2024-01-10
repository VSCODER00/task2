
CC = g++
CFLAGS = -std=c++11

all: labyrinth

labyrinth: labyrinth.cpp
	$(CC) $(CFLAGS) -o labyrinth labyrinth.cpp

clean:
	rm -f labyrinth
