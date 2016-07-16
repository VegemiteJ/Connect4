# Makefile for GameState Unit tests

CLASSES = GameState.o Board.o Node.o Player.o MiniMaxPlayer.o
OBJLOC = ./src/Objs
OBJ = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
VERSION = -std=gnu++14 -Wall -pedantic
CYG = 
LIB =
FLAGS = -g
#Sometimes set flags to -g

#Include files from src
INCLUDE = -I./src

all: gs ai

gs: main

aiTest: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/MiniMaxV01/aiTest.cpp $(OBJ) ${VERSION} ${FLAGS} -o tests/MiniMaxV01/output/aiTest.exe

ai: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/MiniMaxV01/ai.cpp $(OBJ) ${VERSION} ${FLAGS} -o tests/MiniMaxV01/output/ai.exe

node: $(CLASSES)
		g++ ${CYG} ${INCLUDE} tests/NodeTests/nodeT.cpp $(OBJ) ${VERSION} ${FLAGS} -o tests/NodeTests/output/Node.exe

clean: cleanai cleangs cleannode

cleanai:
	rm -f $(OBJLOC)/*.o tests/MiniMaxV01/output/*.exe $(OBJLOC)/*.h.gch

cleangs:
	rm -f $(OBJLOC)/*.o tests/GameStateTests/output/*.exe $(OBJLOC)/*.h.gch

cleannode:
	rm -f $(OBJLOC)/*.o tests/NodeTests/output/*.exe $(OBJLOC)/*.h.gch

# ----------------------------------------------------
# BOARD STUFF	
GameState.o: src/GameState.cpp
	g++ -c ${Include} $^ ${FLAGS} -o $(OBJLOC)/$@

Board.o: src/Board.cpp
	g++ -c ${INCLUDE} $^ ${FLAGS} -o $(OBJLOC)/$@

# AI TYPES	
Node.o: src/Node.cpp
	g++ -c ${INCLUDE} $^ ${FLAGS} -o $(OBJLOC)/$@

Player.o: src/Player.cpp
	g++ -c $^ -o $(OBJLOC)/$@

MiniMaxPlayer.o: src/MiniMaxPlayer.cpp
	g++ -c ${INCLUDE} $^ ${FLAGS} -o $(OBJLOC)/$@

#-----------------------------------------------------
# MAIN
main: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/GameStateTests/GameStateTest.cpp $(OBJ) ${VERSION} ${FLAGS} -o tests/GameStateTests/output/Test.exe