/***
•	Anh Le // First and Last name
•	mle288 // UCSC UserID
•	2024 Winter CS101 PA3
•	README.md // FileName
•	Description to the program // Describe the program 
***/

pa3: List.h List.c Graph.h Graph.c GraphTest.c FindComponents.c Makefile README.md Description: build a Graph module in C that implements the Depth First Search (DFS) algorithm. This program will use the Graph module to find the strongly connected components of a digraph. Recall DFS() calls the recursive algorithm Visit() (referred to as DFS-Visit() in the text), and uses a variable called time that is static over all recursive calls to Visit(). I let time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output variable to Visit(). This is the simplest option.
Compilation: To compile the program, utlized the provided Makefile make makes FindComponents make GraphTest make GraphTest make clean removes all binaries make checkGraphTest checks GraphTest for memory errors make checkFindPath checks FindPath for memory errors
Usage: ./FindComponents 
All the file strucuture: Graph.c: implementation of the grapth ADT structure and the associated function Graph.h: user-interface and header file that contain the associated function of Graph.c and also mask them for private purpose List.h: implementation of the list ADT structure and the associated function List.h: user-interface and header file that contain the associated function of List.c and also mask them for private purpose Makefile: Makefile for easier compilation process FindComponents.c: the main file that utilizes the Graph ADT GraphTest.c: the test file for Graph ADT README.md: description