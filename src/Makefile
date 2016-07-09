# Makefile for connect-four

CLASSES = Board.o Player.o LocalPlayer.o Game.o ClientSocketSet.o ServerSocketSet.o
VERSION = -std=c++11 -Wall -pedantic
LIB = -lws2_32

all: main

clean:
	rm -f *.o ../bin/*
# ----------------------------------------------------
# BOARD STUFF	
Board.o: Board.cpp
	g++ -c $^
# ----------------------------------------------------
# FUNDAMENTAL GAME STUFF
Player.o: Player.cpp
	g++ -c $^

LocalPlayer.o: LocalPlayer.cpp
	g++ -c $^
	
Game.o: Board.h Player.h Game.cpp
	g++ -c $^
# ----------------------------------------------------	
# PLAYER TYPES
Human.o: Player.h Human.cpp 
	g++ -c $^

# Computer: Player Computer.cpp
#	g++ -c Computer.cpp
# ----------------------------------------------------	
# AI TYPES	


# ----------------------------------------------------	
# NETWORKING
Network: ClientSocketSet.o ServerSocketSet.o
	g++ netmainS.cpp $^ ${VERSION} ${LIB} -o ../bin/NetTestS.exe
	g++ netmainC.cpp $^ ${VERSION} ${LIB} -o ../bin/NetTestC.exe

ClientSocketSet.o: ClientSocketSet.h ClientSocketSet.cpp
	g++ -c ${VERSION} ClientSocketSet.cpp -o ClientSocketSet.o

ServerSocketSet.o: ServerSocketSet.h ServerSocketSet.cpp
	g++ -c ${VERSION} ServerSocketSet.cpp -o ServerSocketSet.o

#-----------------------------------------------------
# MAIN
main: ${CLASSES}
	g++ main.cpp ${CLASSES} ${LIB} ${VERSION} -o ../bin/Connect4.exe