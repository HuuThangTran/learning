/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* Lex.c // FileName
* The main program/User interface to run the ADT  // Describe the program
***/

#define _GNU_SOURCE
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 500

int main(int argc, char* argv[]) {
/* Check that there are two command line arguments (other than the program name Lex).  Quit with a usage message to stderr if more than or less than two command line arguments are given.
 Lex.c will take two command line arguments giving the names of an input file and an output file, respectively.
lex <input file> <output file>  
*/
    if (argc != 3) {
    fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
    }
/*
Count the number of lines n in the input file.  Create a string array of length n and read in the lines of the 
file  as  strings,  placing  them  into  the  array.    (Allocate  this  array  from  heap  memory  using  functions 
calloc() or malloc() defined in the header file stdlib.h.  Do not use a variable length array.  See 
the comments here for more on this topic.)
*/

    // open the input file
   FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        exit(EXIT_FAILURE);
    }

    // Count the number of lines in the input file
    int line = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        line++;
    }

    // Array of string
    char **linesArray = (char **)malloc(line * sizeof(char *));
    if (linesArray == NULL) {
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    rewind(inputFile);

    // Read lines from the file and store them in the array
    for (int i = 0; i < line; i++) {
        if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
            free(linesArray);  // Free allocated memory before exiting
            fclose(inputFile);
            exit(EXIT_FAILURE);
        }

        // Allocate memory for the current line and copy it into the array
        linesArray[i] = strdup(buffer);
        if (linesArray[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(linesArray[j]);  // Free previously allocated memory
            }
            free(linesArray);
            fclose(inputFile);
            exit(EXIT_FAILURE);
        }
    }

    // Close the input file
    fclose(inputFile);

    // for (int i = 0; i < line; i ++) {
    //     printf("Array[%i]: %s\n", i, linesArray[i]);
    // }

    /*
    Create a List whose elements are the indices of the above string array.  These indices should be arranged 
    in an order that indirectly sorts the array.  Using the above input file as an example we would have. 
    
    Indices:     0     1      2      3      4 
    Array:     one   two   three   four   five 
    
    
    
    List:          4     3      0      2      1 
    
    To build the integer List in the correct order, begin with an initially empty List, then insert the indices of 
    the array one by one into the appropriate positions of the List.  Use the Insertion Sort algorithm (section 
    2.1 of the text CLRS) as a guide to your thinking on how to accomplish this.  (Please read the preceding 
    two sentences several times so that you understand what is required.  You are not being asked to sort the 
    input array using Insertion Sort.)  You may use only the List ADT operations defined below to manipulate 
    2 
    the List.  Note that the C standard library string.h provides a function called strcmp() that determines 
    the lexicographic ordering of two Strings.  If s1 and s2 are strings then: 
    
    strcmp(s1, s2)<0 is true if and only if s1 comes before s2 
    strcmp(s1, s2)>0 is true if and only if s1 comes after s2 
    strcmp(s1, s2)==0 is true if and only if s1 is identical to s2
    */
    // new list
    List indicesList = newList();
    // Append the indices of the first character of the array
    append(indicesList, 0);

    // insert the indices base on the alphabetical order of the array
    for (int i = 1; i < line; i++) {
            moveFront(indicesList); // Start at the front of the List

            // Find the correct position to insert the current index
            while (listIndex(indicesList) != -1 && strcmp(linesArray[get(indicesList)], linesArray[i]) < 0) {
                moveNext(indicesList);
            }

            // Insert the current index at the correct position
            if (listIndex(indicesList) == -1) {
                // If cursor is undefined, append the index
                append(indicesList, i);
            } else {
                // If cursor is defined, insert before the cursor
                insertBefore(indicesList, i);
            }
    }
    // printList(stdout, indicesList);

    // Print the array in alphabetical order to the output file
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        freeList(&indicesList);
        return EXIT_FAILURE;
    }

    // Print the array based on the sorted indices
    moveFront(indicesList);
    while (listIndex(indicesList) != -1) {
        fprintf(outputFile, "%s", linesArray[get(indicesList)]);
        moveNext(indicesList);
    }

    // Close the output file
    fclose(outputFile);

    // Free memory associated with the List
    freeList(&indicesList);


    // Free allocated memory for each line and the array itself
    for (int i = 0; i < line; i++) {
        free(linesArray[i]);
    }
    free(linesArray);

}
