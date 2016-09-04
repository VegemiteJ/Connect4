# Makefile for connect-four

CLASSES = GameState.o Node.o Board.o Player.o MiniMaxPlayer.o LocalPlayer.o RandomPlayer.o Game.o
NETCLASSES = ClientSocketSet.o ServerSocketSet.o NetworkPlayer.o
HELPCLASSES = PrintConsole.o Params.o 

#Store all objects in a Obj folder, seperate from src files
OBJLOC = ./Objs
OBJS = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
NOBJS = $(patsubst %,$(OBJLOC)/%,$(NETCLASSES))
HOBJS = $(patsubst %,$(OBJLOC)/%,$(HELPCLASSES))
VERSION = -std=gnu++14 -Wall -pedantic -O3
CYG = -g
LIB = 
INCLUDE = -I"/usr/include"

all: main

clean:
	rm -f Objs/*.o ../bin/* *.h.gch
# ----------------------------------------------------

# BOARD STUFF	
GameState.o: GameState.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

Board.o: Board.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@
# ----------------------------------------------------

# FUNDAMENTAL GAME STUFF	
Game.o: Game.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

# ----------------------------------------------------	

# PLAYER TYPES
Player.o: Player.cpp
	g++ -c $^ ${CYG} -o $(OBJLOC)/$@

LocalPlayer.o: LocalPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

NetworkPlayer.o: NetworkPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

RandomPlayer.o: RandomPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@

MiniMaxPlayer.o: MiniMaxPlayer.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@
# ----------------------------------------------------	

# AI TYPES	
Node.o: Node.cpp
	g++ -c ${VERSION} $^ ${CYG} -o $(OBJLOC)/$@
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

#-----------------------------------------------------
# HELPER FUNCTIONS
PrintConsole.o: PrintConsole.cpp
	g++ -c ${INCLUDE} $^ ${FLAGS} ${VERSION} -o $(OBJLOC)/$@

Params.o: Params.cpp
	g++ -c ${INCLUDE} $^ ${FLAGS} ${VERSION} -o $(OBJLOC)/$@
#-----------------------------------------------------

# MAIN
main: ${HELPCLASSES} ${NETCLASSES} ${CLASSES}
	g++ ${CYG} main.cpp $(HOBJS) $(OBJS) ${LIB} ${VERSION} -o ../bin/Connect4_3X6O.exe