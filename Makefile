all: bs

bs: bsTest.o player.o ship.o board.o
	g++ -o bs bsTest.o player.o ship.o board.o
bsTest.o: bsTest.cpp player.h ship.h board.h
	g++ -c bsTest.cpp
player.o: player.cpp player.h ship.h board.h
	g++ -c player.cpp
ship.o: ship.cpp ship.h player.h board.h
	g++ -c ship.cpp
board.o: board.cpp board.h ship.h player.h
	g++ -c board.cpp

clean:
	rm bs bsTest.o player.o ship.o board.o 

