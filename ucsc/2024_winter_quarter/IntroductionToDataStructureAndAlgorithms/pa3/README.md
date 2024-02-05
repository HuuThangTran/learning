/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* README.md // FileName
* Description to the program // Describe the program
***/

pa2: FindPath.c Graph.c Graph.h GraphTest.c List.c List.h Makefile README.md
Description: The problem FindPath.c is the user interface that utlized the implementation of a Graph ADT and some associated algorithms in C. This project will utilize your List ADT from pa1

Compilation: To compile the program, utlized the provided Makefile
make                   makes FindPath
make GraphTest		   make GraphTest
make clean             removes all binaries
make checkGraphTest    checks GraphTest for memory errors
make checkFindPath     checks FindPath for memory errors

Usage: ./FindPath <infile> <outfile>

All the file strucuture:
Graph.c: implementation of the grapth ADT structure and the associated function
Graph.h: user-interface and header file that contain the associated function of Graph.c and also mask them for private purpose
List.h: implementation of the list ADT structure and the associated function
List.h: user-interface and header file that contain the associated function of List.c and also mask them for private purpose
Makefile: Makefile for easier compilation process 
FindPath.c: the main file that utilizes the Graph ADT
GraphTest.c: the test file for Graph ADT
README.md: description
