#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes FindPath
# make GraphTest		 make GraphTest
# make clean             removes all binaries
# make checkGraphTest    checks GraphTest for memory errors
# make checkFindPath     checks FindPath for memory errors
#------------------------------------------------------------------------------

CC = gcc
CFLAGS =-std=c17 -Wall

Graph: Graph.o List.o
	$(CC) $(CFLAGS) -o Graph Graph.o List.o

Graph.o : Graph.c List.h
	$(CC) $(CFLAGS) -c Graph.c

# FindPath : FindPath.o Graph.o List.o
# 	$(CC) $(CFLAGS) -o FindPath FindPath.o Graph.o List.o

# FindPath.o : FindPath.c Graph.h List.h
# 	$(CC) $(CFLAGS) -c FindPath.c

# Graph.o : Graph.c Graph.h List.h
# 	$(CC) $(CFLAGS) -c Graph.c

# GraphTest : GraphTest.o Graph.o List.o
# 	$(CC) $(CFLAGS) -o GraphTest GraphTest.o Graph.o List.o

# GraphTest.o : GraphTest.c Graph.h List.h
# 	$(CC) $(CFLAGS) -c GraphTest.c

List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

clean :
	rm -f FindPath GraphTest *.o

checkGraphTest : 
	valgrind --leak-check=full GraphTest

checkFindPath :
	valgrind --leak-check=full FindPath in3 blah3