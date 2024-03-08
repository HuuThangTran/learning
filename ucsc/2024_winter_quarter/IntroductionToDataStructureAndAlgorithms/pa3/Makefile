#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes FindComponnets 
# make GraphTest		 make GraphTest
# make clean             removes all binaries
# make checkGraphTest    checks GraphTest for memory errors
# make checkFindPath     checks FindPath for memory errors
#------------------------------------------------------------------------------

CC = gcc
CFLAGS =-std=c17 -Wall

FindComponents : FindComponents.o Graph.o List.o
	$(CC) $(CFLAGS) -o FindComponents FindComponents.o Graph.o List.o

FindComponents.o : FindComponents.c Graph.h List.h
	$(CC) $(CFLAGS) -c FindComponents.c

Graph.o : Graph.c Graph.h List.h
	$(CC) $(CFLAGS) -c Graph.c

List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

GraphTest : GraphTest.o Graph.o List.o
	$(CC) $(CFLAGS) -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.h List.h
	$(CC) $(CFLAGS) -c GraphTest.c

clean :
	rm -f FindComponents GraphTest *.o

checkGraphTest : 
	valgrind --leak-check=full GraphTest

checkFindPath :
	valgrind --leak-check=full FindPath in3 blah3