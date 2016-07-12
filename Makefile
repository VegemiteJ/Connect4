# Makefile for GameState Unit tests

CLASSES = GameState.o Board.o Node.o
OBJLOC = ./tests/GameStateTests
OBJS = $(patsubst %,$(OBJLOC)/%,$(CLASSES))
VERSION = -std=gnu++14 -Wall -pedantic
CYG = 
LIB = -L./tests/GameStateTests

#Include files from src
INCLUDE = -I./src -I./tests/GameStateTests

all: main

clean:
	rm -f tests/GameStateTests/*.o output/Test.exe *.h.gch
# ----------------------------------------------------
# BOARD STUFF	
GameState.o: src/GameState.cpp
	g++ -c ${Include} $^ -o tests/GameStateTests/GameState.o

Board.o: src/Board.cpp
	g++ -c ${INCLUDE} $^ -o tests/GameStateTests/Board.o

# AI TYPES	
Node.o: src/Node.cpp
	g++ -c ${INCLUDE} $^ -o tests/GameStateTests/Node.o


#-----------------------------------------------------
# MAIN
main: $(CLASSES)
	g++ ${CYG} ${INCLUDE} tests/GameStateTests/GameStateTest.cpp $(OBJS) ${VERSION} -o tests/GameStateTests/output/Test.exe