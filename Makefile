# Makefile for GameState Unit tests

CLASSES = GameState.o Board.o Node.o
OBJLOC = ./src/Objs
OBJ = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
VERSION = -std=gnu++14 -Wall -pedantic
CYG = 
LIB = -L./tests/GameStateTests

#Include files from src
INCLUDE = -I./src -I./tests/GameStateTests

all: gs ai

gs: main

aiTest: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/MiniMaxV01/aiTest.cpp $(OBJ) ${VERSION} -o tests/MiniMaxV01/output/aiTest.exe

ai: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/MiniMaxV01/ai.cpp $(OBJ) ${VERSION} -o tests/MiniMaxV01/output/ai.exe

clean:
	rm -f $(OBJLOC)/*.o $(OBJLOC)/output/ai.exe $(OBJLOC)/*.h.gch
# ----------------------------------------------------
# BOARD STUFF	
GameState.o: src/GameState.cpp
	g++ -c ${Include} $^ -o $(OBJLOC)/GameState.o

Board.o: src/Board.cpp
	g++ -c ${INCLUDE} $^ -o $(OBJLOC)/Board.o

# AI TYPES	
Node.o: src/Node.cpp
	g++ -c ${INCLUDE} $^ -o $(OBJLOC)/Node.o


#-----------------------------------------------------
# MAIN
main: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/GameStateTests/GameStateTest.cpp $(OBJ) ${VERSION} -o tests/GameStateTests/output/Test.exe