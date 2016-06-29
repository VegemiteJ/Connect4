# Makefile for connect-four

CLASSES = Board.o Player.o Game.o

all: main

clean:
	rm -f *.o ../bin/*
# ----------------------------------------------------
# BOARD STUFF	
Board: Board.cpp
	g++ -c $^
# ----------------------------------------------------
# FUNDAMENTAL GAME STUFF
Player: Player.cpp
	g++ -c $^
	
Game: Game.cpp Board.o Player.o
	g++ -c $^
# ----------------------------------------------------	
# PLAYER TYPES
Human: Human.cpp Player.o
	g++ -c $^

# Computer: Player Computer.cpp
#	g++ -c Computer.cpp
# ----------------------------------------------------	
# AI TYPES	


# ----------------------------------------------------	
# MAIN
main: main.cpp $(CLASSES)
	g++ -o ../bin/Connect4.exe $^