#    Anh Le // First and Last name
#    mle288 // UCSC UserID
#    2024 Winter CS101 PA5
#    Makefile// FileName
#    For convenient for make short key in terminal, compilation of files, objectfiles // Describe the program


#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 5
#
# make                   makes Shuffle 
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkListTest     checks ListTest for memory errors
# make checkShuffle      checks Shuffle for memory errors
#------------------------------------------------------------------------------

CC = g++
CFLAGS =-std=c++11 -Wall

Shuffle : Shuffle.o List.o
	$(CC) $(CFLAGS) -o Shuffle Shuffle.o List.o

Shuffle.o : Shuffle.cpp List.h
	$(CC) $(CFLAGS) -c Shuffle.cpp

ListTest : ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

ListTest.o : ListTest.cpp List.h
	$(CC) $(CFLAGS) -c ListTest.cpp

List.o : List.h List.cpp
	$(CC) $(CFLAGS) -c List.cpp

clean:
	rm -f Shuffle ListTest *.o

checkListTest :
	valgrind --leak-check=full ./ListTest

checkShuffle :
	valgrind --leak-check=full ./Shuffle 35