#include "Graph.h"
#include <stdlib.h>

#define COLOR_WHITE ((char)0)
#define COLOR_GRAY  ((char)1)
#define COLOR_BLACK ((char)2)

struct GraphObj {
  int   order; // order or the graph (number of vertices)
  int   size;  // size of the graph (number of undirected edges)
  List* neighbors;
  char* color;
  int*  parent;
  int*  distance;
  int   source;
};

Graph newGraph(int n) {
  Graph G      = (Graph)malloc(sizeof(struct GraphObj));
  G->order     = n;
  G->size      = 0;
  G->neighbors = (List*)malloc(sizeof(List) * (n + 1));
  G->color     = (char*)malloc(sizeof(char) * (n + 1));
  G->parent    = (int*) malloc(sizeof(int)  * (n + 1));
  G->distance  = (int*) malloc(sizeof(int)  * (n + 1));
  for (int i = 1; i <= n; i ++) {
    G->neighbors[i] = newList();
    G->color[i]     = COLOR_WHITE;
    G->parent[i]    = NIL;
    G->distance[i]  = INF;
  }
  G->source = NIL;
  return G;
}

void freeGraph(Graph* pG) {
  for (int i = 1; i <= (*pG)->order; i ++) {
    List neighbors = (*pG)->neighbors[i];
    freeList(&neighbors);
  }
  free((*pG)->neighbors);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);
  *pG = NULL;
}

int getOrder(Graph G) {
  return G->order;
}


int getSize(Graph G) {
  return G->size;
}

int getSource(Graph G) {
  return G->source;
}

int getParent(Graph G, int u) {
  if (u < 1 || u > getOrder(G)) {
    printf("getParent ERROR: u < 1 || u > G->getOrder()\n");
    exit(-1);
  }
  return G->parent[u];
}

int getDist(Graph G, int u) {
  if (u < 1 || u > getOrder(G)) {
    printf("getDist ERROR: u < 1 || u > G->getOrder()\n");
    exit(-1);
  }
  return G->distance[u];
}

void makeNull(Graph G) {
  for (int i = 1; i <= G->order; i ++) {
    listClear(G->neighbors[i]);
  }
  G->size = 0;
}

// Adds directed edge without modifying size (addEdge and addArc use
// this and modify size differently below)
void addArcHelper(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("addArc ERROR: u < 1 || u > G->getOrder()\n");
    exit(-1);
  }
  if (v < 1 || v > getOrder(G)) {
    printf("addArc ERROR: v < 1 || v > G->getOrder()\n");
    exit(-1);
  }
  List neighbors = G->neighbors[u];
  moveFront(neighbors);
  while (listIndex(neighbors) >= 0) {
    int k = get(neighbors);
    if (k > v) {
      insertBefore(neighbors, v);
      return;
    } else if (k == v) {
      return;
    }
    moveNext(neighbors);
  }
  append(neighbors, v);
}

void addArc(Graph G, int u, int v) {
  addArcHelper(G, u, v);
  G->size ++;
}

void addEdge(Graph G, int u, int v) {
  if (u < 1 || u > getOrder(G)) {
    printf("addEdge ERROR: u < 1 || u > G->getOrder()\n");
    exit(-1);
  }
  if (v < 1 || v > getOrder(G)) {
    printf("addEdge ERROR: v < 1 || v > G->getOrder()\n");
    exit(-1);
  }
  addArcHelper(G, u, v);
  addArcHelper(G, v, u);
  G->size ++;
}

void printGraph(FILE* out, Graph G) {
  for (int i = 1; i <= G->order; i ++) {
    fprintf(out, "%d:", i);
    List neighbors = G->neighbors[i];
    moveFront(neighbors);
    while (listIndex(neighbors) >= 0) {
      int v = get(neighbors);
      fprintf(out, " %d", v);
      moveNext(neighbors);
    }
    fprintf(out, "\n");
  }
}

void BFS(Graph G, int s) {
  if (s < 1 || s > getOrder(G)) {
    printf("BFS ERROR: s < 1 || s > G->getOrder()\n");
    exit(-1);
  }
  // initialize vertices
  for (int i = 1; i <= G->order; i ++) {
    if (i == s) {
      G->color[i]    = COLOR_GRAY;
      G->distance[i] = 0;
      G->parent[i]   = NIL;
    } else {
      G->color[i]    = COLOR_WHITE;
      G->distance[i] = INF;
      G->parent[i]   = NIL;
    }
  }
  // initialize source
  G->source = s;
  // initialize Q
  List Q = newList();
  append(Q, s);
  // loop and expand frontier
  while (length(Q) != 0) {
    moveFront(Q);
    int x = get(Q);
    deleteFront(Q);
    List neighbors = G->neighbors[x];
    moveFront(neighbors);
    while (listIndex(neighbors) >= 0) {
      int y = get(neighbors);
      if (G->color[y] == COLOR_WHITE) {
    G->color[y]    = COLOR_GRAY;
    G->distance[y] = G->distance[x] + 1;
    G->parent[y]   = x;
    append(Q, y);
      }
      moveNext(neighbors);
    }
    G->color[x] = COLOR_BLACK;
  }
  freeList(&Q);
}

void getPath(List L, Graph G, int u) {
  if (getSource(G) == NIL) {
    printf("getPath ERROR: getSource(G) == NIL\n");
    exit(-1);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("getPath ERROR: u < 1 || u > G->getOrder()\n");
    exit(-1);
  }
  if (G->color[u] == COLOR_WHITE) {
    append(L, NIL);
    return;
  }
  List P = newList();
  int  x = u;
  while (x != G->source) {
    prepend(P, x);
    x = getParent(G, x);
  }
  prepend(P, G->source);
  moveFront(P);
  while (listIndex(P) >= 0) {
    x = get(P);
    append(L, x);
    moveNext(P);
  }
  freeList(&P);
}
