#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

int countLinesInFile(FILE* inFile) {
  char ch;
  int  lineExists = 0;
  int  lineNumber = 0;
  int  done       = 0;
  clearerr(inFile);
  fseek(inFile, 0, SEEK_SET);
  while (! done) {
    ch = fgetc(inFile);
    if (feof(inFile)) {
      done = 1;
    } else {
      lineExists = 1;
      if (ch == '\n') {
    lineNumber ++;
    lineExists = 0;
      }
    }
  }
  if (lineExists) {
    lineNumber ++;
  }
  return lineNumber;
}

int readLineLengthFromFile(FILE* inFile) {
  int  offset = ftell(inFile);
  int  done   = 0;
  int  len    = 0;
  char ch;
  while (! done) {
    ch = fgetc(inFile);
    if (feof(inFile)) {
      done = 1;
    } else {
      if (ch == '\n') {
    done = 1;
      } else {
    len ++;
      }
    }
  }
  clearerr(inFile);
  fseek(inFile, offset, SEEK_SET);
  return len;
}

void readLineFromFile(FILE* inFile, char* str) {
  int  done  = 0;
  int  index = 0;
  char ch;
  while (! done) {
    ch = fgetc(inFile);
    if (feof(inFile)) {
      done = 1;
    } else {
      if (ch == '\n') {
    done = 1;
      } else {
    str[index] = ch;
    index ++;
      }
    }
  }
  str[index] = '\0';
}

void readLinesFromFile(FILE* inFile, char** array) {
  int done      = 0;
  int lineIndex = 0;
  int len;
  clearerr(inFile);
  fseek(inFile, 0, SEEK_SET);
  
  while (! done) {
    len = readLineLengthFromFile(inFile);
    if (len == 0) {
      done = 1;
    } else {
      array[lineIndex] = (char*)malloc(sizeof(char) * (len + 1));
      readLineFromFile(inFile, array[lineIndex]);
      if (feof(inFile)) {
    done = 1;
      }
      lineIndex ++;
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("USAGE: FindPath <infile> <outfile>\n");
    exit(-1);
  }
  char* inFileName  = argv[1];
  char* outFileName = argv[2];
  printf("FindPath %s %s\n", inFileName, outFileName);
  FILE* inFile = fopen(inFileName, "r");
  if (inFile == NULL) {
    printf("FinPath Error: Cannot open \"%s\" for reading.\n", inFileName);
    exit(1);
  }
  FILE* outFile = fopen(outFileName, "w");
  if (outFile == NULL) {
    printf("FinPath Error: Cannot open \"%s\" for writing.\n", inFileName);
    exit(1);
  }
  
  int    lineNumber = countLinesInFile(inFile);
  char** array      = (char**)malloc(sizeof(char*) * lineNumber);
  readLinesFromFile(inFile, array);
  
  //{
  //  for (int i = 0; i < lineNumber; i ++) {
  //    printf("array[%d] = \"%s\"\n", i, array[i]);
  //  }
  //}
  
  int   order = atoi(array[0]);
  Graph G     = newGraph(order);
  int   i     = 1;
  {
    int u = -1;
    int v = -1;
    while (u != 0 && v != 0) {
      char* next;
      u = strtol(array[i], &next, 10);
      v = strtol(next, NULL, 10);
      //printf("(u,v) = (%d,%d)\n", u, v);
      if (u != 0 && v != 0) {
    addEdge(G, u, v);
      }
      i ++;
    }
  }
  
  printGraph(outFile, G);
  
  {
    int s = -1;
    int d = -1;
    while (s != 0 && d != 0) {
      char* next;
      s = strtol(array[i], &next, 10);
      d = strtol(next, NULL, 10);
      //printf("(s,d) = (%d,%d)\n", s, d);
      if (s != 0 && d != 0) {
    fprintf(outFile, "\n");
    List L = newList();
    BFS(G, s);
    getPath(L, G, d);
    moveFront(L);
    if (get(L) == NIL) {
      fprintf(outFile, "The distance from %d to %d is infinity\n", s, d);
      fprintf(outFile, "No %d-%d path exists\n", s, d);
    } else {
      fprintf(outFile, "The distance from %d to %d is %d\n", s, d, getDist(G, d));
      fprintf(outFile, "A shortest %d-%d path is:", s, d);
      while (listIndex(L) >= 0) {
        fprintf(outFile, " %d", get(L));
        moveNext(L);
      }
      fprintf(outFile, "\n");
    }
    freeList(&L);
      }
      i ++;
    }
  }
  
  fclose(outFile);
  fclose(inFile);

  freeGraph(&G);
  for (i = 0; i < lineNumber; i ++) {
    free(array[i]);
  }
  free(array);
  return 0;
}
