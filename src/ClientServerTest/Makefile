#!/bin/bash
OPTIONS = -std=c++11 -lws2_32

main: clean default

clean:
	rm *.o *.exe

default: client.o server.o
	g++ client.o ${OPTIONS} -o client.exe
	g++ server.o ${OPTIONS} -o server.exe

client: client.cpp
	g++ client.cpp -c client.o

server: server.cpp
	g++ server.cpp -c server.o