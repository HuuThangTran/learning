#ifndef GRAPH__H
#define GRAPH__H

#include "List.h"

typedef struct GraphObj* Graph;

#define INF ((int)-1)
#define NIL ((int)0)

Graph newGraph  (int n);
void  freeGraph (Graph* pG);
int   getOrder  (Graph G);
int   getSize   (Graph G);
int   getSource (Graph G);
int   getParent (Graph G, int u);
int   getDist   (Graph G, int u);
void  makeNull  (Graph G);
void  addArc    (Graph G, int u, int v);
void  addEdge   (Graph G, int u, int v);
void  printGraph(FILE* out, Graph G);
void  BFS       (Graph G, int s);
void  getPath   (List L, Graph G, int u);

#endif // GRAPH__H
