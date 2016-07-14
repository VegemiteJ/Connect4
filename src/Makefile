# Makefile for connect-four

CLASSES = GameState.o Node.o Board.o Player.o MiniMaxPlayer.o LocalPlayer.o NetworkPlayer.o RandomPlayer.o Game.o ClientSocketSet.o ServerSocketSet.o
NETCLASSES = ClientSocketSet.o ServerSocketSet.o
OBJLOC = ./Objs
OBJS = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
NOBJS = $(patsubst %,$(OBJLOC)/%,$(NETCLASSES))
VERSION = -std=gnu++14 -Wall -pedantic
CYG = 
LIB = -lws2_32
INCLUDE = -I"/usr/include"

all: main

clean:
	rm -f Objs/*.o ../bin/* *.h.gch
# ----------------------------------------------------
# BOARD STUFF	
GameState.o: GameState.cpp
	g++ -c $^ -o $(OBJLOC)/$@

Board.o: Board.cpp
	g++ -c $^ -o $(OBJLOC)/$@
# ----------------------------------------------------
# FUNDAMENTAL GAME STUFF
Player.o: Player.cpp
	g++ -c $^ -o $(OBJLOC)/$@

LocalPlayer.o: LocalPlayer.cpp
	g++ -c $^ -o $(OBJLOC)/$@

NetworkPlayer.o: NetworkPlayer.cpp
	g++ -c ${VERSION} $^ -o $(OBJLOC)/$@

RandomPlayer.o: RandomPlayer.cpp
	g++ -c ${VERSION} $^ -o $(OBJLOC)/$@

MiniMaxPlayer.o: MiniMaxPlayer.cpp
	g++ -c ${INCLUDE} $^ -o $(OBJLOC)/$@
	
Game.o: Game.cpp
	g++ -c ${VERSION} $^ -o $(OBJLOC)/$@
# ----------------------------------------------------	
# PLAYER TYPES
Human.o: Player.h Human.cpp 
	g++ -c $^ -o $(OBJLOC)/$@

# Computer: Player Computer.cpp
#	g++ -c Computer.cpp
# ----------------------------------------------------	
# AI TYPES	
Node.o: Node.cpp
	g++ -c $^ -o $(OBJLOC)/$@

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
main: ${CLASSES}
	g++ ${CYG} main.cpp $(OBJS) ${LIB} ${VERSION} -o ../bin/Connect4.exe