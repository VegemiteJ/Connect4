# Makefile for connect-four

CLASSES = GameState.o Node.o Board.o Player.o MiniMaxPlayer.o LocalPlayer.o RandomPlayer.o Game.o
NETCLASSES = ClientSocketSet.o ServerSocketSet.o NetworkPlayer.o

#Store all objects in a Obj folder, seperate from src files
OBJLOC = ./Objs
OBJS = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
NOBJS = $(patsubst %,$(OBJLOC)/%,$(NETCLASSES))
VERSION = -std=gnu++0x -Wall -pedantic -O3
CYG = -g
LIB = 
INCLUDE = -I"/usr/include"

all: main

clean:
	rm -f Objs/*.o ../bin/* *.h.gch
# ----------------------------------------------------

# BOARD STUFF	
GameState.o: GameState.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@

Board.o: Board.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@
# ----------------------------------------------------

# FUNDAMENTAL GAME STUFF	
Game.o: Game.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

# ----------------------------------------------------	

# PLAYER TYPES
Player.o: Player.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@

LocalPlayer.o: LocalPlayer.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@

NetworkPlayer.o: NetworkPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

RandomPlayer.o: RandomPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

MiniMaxPlayer.o: MiniMaxPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@
# ----------------------------------------------------	

# AI TYPES	
Node.o: Node.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@
# ----------------------------------------------------	

# NETWORKING
Network: ClientSocketSet.o ServerSocketSet.o
	g++ netmainS.cpp $(NOBJS) ${VERSION} ${LIB} -o ../bin/NetTestS.exe
	g++ netmainC.cpp $(NOBJS) ${VERSION} ${LIB} -o ../bin/NetTestC.exe

ClientSocketSet.o: ClientSocketSet.h ClientSocketSet.cpp
	g++ -c ${VERSION} ${INCLUDE} ClientSocketSet.cpp -o $(OBJLOC)/$@

ServerSocketSet.o: ServerSocketSet.h ServerSocketSet.cpp
	g++ -c ${VERSION} ${INCLUDE} ServerSocketSet.cpp -o $(OBJLOC)/$@
#-----------------------------------------------------

# MAIN
main: ${NETCLASSES} ${CLASSES}
	g++ ${CYG} main.cpp $(OBJS) ${LIB} ${VERSION} -o ../bin/Connect4.exe