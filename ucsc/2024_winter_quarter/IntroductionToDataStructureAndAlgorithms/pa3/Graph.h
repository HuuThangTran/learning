/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* README.md // FileName
* Graph.h Private and hide the the fucntion from Graph.c to the user and create and define a header file // Describe the program
***/

#ifndef GRAPH__H
#define GRAPH__H

#include "List.h"

/*macros INF and NIL that represent infinity and an undefined vertex label, respectively. For the purpose of
implementing BFS, any negative int value is an adequate choice for INF, and any non-positive int can
stand in for NIL, since all valid vertex labels will be positive integers. INF and NIL should of course be
different integers.
*/
// #define constant
#define INF ((int)-1)
#define NIL ((int)0)

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph  (int n);
void  freeGraph (Graph* pG);

/*** Access functions ***/
// pa2
int   getSource (Graph G);
// pa2
int   getDist   (Graph G, int u);
//pa2
void  getPath   (List L, Graph G, int u);

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif // GRAPH__H



// // Constructors-Destructors
// Graph newGraph(int n);
// void freeGraph(Graph* pG);
// // Access functions
// int getOrder(Graph G);
// int getSize(Graph G);
// int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// // Manipulation procedures
// void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
// void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
// void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
// // Other Functions
// Graph transpose(Graph G);
// Graph copyGraph(Graph G);
// void printGraph(FILE* out , Graph G);