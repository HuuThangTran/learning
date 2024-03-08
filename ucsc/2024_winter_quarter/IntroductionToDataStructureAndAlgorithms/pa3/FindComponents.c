/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* README.md // FileName
* FindComponents.c the main program user interface 
***/

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100


int main(int argc, char* argv[]) {
    // Check that there are two command line argument
    if (argc != 3) {
        printf("Usage: ./FindPath input_file output_file\n");
        exit(EXIT_FAILURE);
    }

    // Open the input file and exit if cannot
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("No inputfile with name %s is found\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Error: cannot open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Count the number of line in the input file
    int line = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        line++;
    }
    // printf("The number of line: %i\n", line);

    // In case of no line in the text file which can result in segmentation fault we exit 
    if (line == 0) {
        printf("No script in %s file\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    rewind(inputFile);

    // the first line is the number of vertices
    int numVertices;
    // REad the first line into the integer   
    if (fscanf(inputFile, "%d", &numVertices) != 1) {
        printf("Error while reading the number of vertices.\n");
        fclose(inputFile);
        return 1;
    }
    Graph G = newGraph(numVertices);
    // printf("Order: %i\n", G->order);
    // printf("The nubmer of vertices: %i\n", numVertices);

    // Reading the next folliwing lines for vertices sources and their destination to implement edges
    int src, dest;
    while (fscanf(inputFile, "%d %d", &src, &dest) == 2 && (src != 0 && dest != 0)) {
        // Print the line
        addArc(G, src, dest);
    }
    // Print out the size to check Size: the number of edges
    // printf("size: %i\n", G->size);

    // Print out to the ouput file, now printing to the terminal to check
    // printf("Output:\nAdjacency list representation of G:\n");
    // printGraph(stdout,G);
    fprintf(outputFile, "Output:\nAdjacency list representation of G:\n");
    printGraph(outputFile, G);

    // Creating a List to process the DFS
    /*
    - the order of G is 8 which corresponding to the number of vertices input
    - we need to create L which is a list that have 8 corresponding dobuly nodes
    */
    // int a = l(L);
    fprintf(outputFile,"\n");

    FindSCC(G, outputFile);
    freeGraph(&G);
}


