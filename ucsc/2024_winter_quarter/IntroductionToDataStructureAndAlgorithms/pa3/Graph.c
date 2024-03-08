/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* README.md // FileName
* Graph.c the implementation of the function declare in graph.h // Describe the program
***/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>


#define COLOR_WHITE ((char)0)
#define COLOR_GRAY  ((char)1)
#define COLOR_BLACK ((char)2)


/*** Constructors-Destructors ***/
Graph newGraph (int n) {
    // Function newGraph() will return a reference to a new graph object containing n vertices and no edges.
    // where 𝑛 is the number of vertices in the graph
    Graph G = (Graph)malloc(sizeof(struct GraphObj));
    // field storing the number of vertices
    G->order = n;
    // the nubmer of edge
    G->size = 0;
    // It is recommended that all arrays be of length 𝑛 + 1
    G->adjacencyList = (List*)malloc(sizeof(List)*(n+1));
    G->color = (char*)malloc(sizeof(char)*(n+1));
    G->parent = (int*)malloc(sizeof(int)*(n+1));
    G-> discovery = (int*)malloc(sizeof(int)*(n+1));
    G-> finish = (int*)malloc(sizeof(int)*(n+1));
    // Assinging the value for the n vertices, marked them as white with 
    for (int i = 1; i <= n; i ++) {
        G->adjacencyList[i] = newList();
        G->color[i]     = COLOR_WHITE;
        //Note that the parent of a vertex may be NIL. The discover and finish times of vertices will be undefined before DFS is called. 
        G->parent[i]    = NIL;
        G->discovery[i]  = INF;
        G->finish[i] = INF;
    }
    return G;
}
void  freeGraph (Graph* pG) {
    //pG is a pointer to a graph pointer that have adjecency pointed to a list array
    // free that list array
    for (int i = 1; i <= (*pG)->order; i ++) {
        List adjacencyList = (*pG)->adjacencyList[i];
        freeList(&adjacencyList);
    }
    // free all the borrow malloc memory in *pG
    free((*pG)->adjacencyList);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/
// getOrder() returns the number of vertices in 𝐺
int getOrder  (Graph G) {
    return G->order;
}

/*
while functions getParent(), getDiscover(), and getFinish()
return the appropriate field values for the given vertex. Note that the parent of a vertex may be NIL. The
discover and finish times of vertices will be undefined before DFS is called.
*/
 
int getSize(Graph G) {
    return G->size;
}

//getParent() will return the parent of vertex u
int getParent(Graph G, int u) {
    /* 
    Note that the parent of a vertex may be NIL. The
discover and finish times of vertices will be undefined before DFS is called. You must #define constant
macros for NIL and UNDEF representing those values and place the definitions in the Graph.h. 
    */
    /* Pre: 1<=u<=n=getOrder(G) */
    // that veticies can only 
    if (u < 1 || u > getOrder(G)) {
    printf("getParrent ERROR: u < 1 || u > G->getOrder()\n");
    exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    /* Pre: 1<=u<=n=getOrder(G) */
    if (u < 1 || u > getOrder(G)) {
    printf("getDiscorver ERROR: u < 1 || u > G->getOrder()\n");
    exit(EXIT_FAILURE);
    }
    return G->discovery[u];
}
int getFinish(Graph G, int u) {
    /* Pre: 1<=u<=n=getOrder(G) */ 
    if (u < 1 || u > getOrder(G)) {
    printf("getDiscorver ERROR: u < 1 || u > G->getOrder()\n");
    exit(EXIT_FAILURE);
    }
    return G->finish[u];
}


/*** Manipulation procedures ***/
void  makeNull  (Graph G);

/*
Function addEdge()
inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
Your program is required to maintain these lists in sorted order by increasing labels. 
* Both addEdge() and addArc() have the precondition that their two int arguments must lie
in the range 1 to getOrder(G).

*/

void insertVertices(Graph G, int u, int v) {
    /* Pre: 1<=u<=n, 1<=v<=n */
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Violation of precondition: Vertex indeces must be in the range of 1 to %i\n",G->order);
        exit(EXIT_FAILURE);
    }
    List adjacencyList = G->adjacencyList[u];
    moveFront(adjacencyList);
    // Checking the cursor is at valid position 
    while (index(adjacencyList) >= 0) {
        // getting the data the cursor element is pointed to which is the vertices neighbor of vertices u
        int k = get(adjacencyList);
        // if the current cursor have int data > than the value of the value of vertices neight we want to input in
        if (k > v) {
            insertBefore(adjacencyList,v);
            return;
        }else if (k == v) {
            return;
        }
        moveNext(adjacencyList);
    }
    // Add the vertices to the last node
    append(adjacencyList, v);
} 

void addEdge(Graph G, int u, int v) {
    /* Pre: 1<=u<=n, 1<=v<=n */
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Violation of precondition: Vertex indeces must be in the range of 1 to %i\n",G->order);
        exit(EXIT_FAILURE);
    }
    insertVertices(G,u,v);
    insertVertices(G,v,u);
    G->size ++;
}

/*
Function addArc()
inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency
List of v). 
*/

void addArc(Graph G, int u, int v) {
    /* Pre: 1<=u<=n, 1<=v<=n */
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Violation of precondition: Vertex indeces must be in the range of 1 to %i\n",G->order);
        exit(EXIT_FAILURE);
    }
    insertVertices(G,u,v);
    G->size ++;
}


// helper function for DFS
void visit(Graph G, int u, List S, int* time) {
    //     1. 𝑑[𝑥] = (+ + time) // discover 𝑥
    G->discovery[u] = ++(*time);
    // printf("Will be vising %d \n", u);
    // 2. color[𝑥] = gray
    G->color[u] = COLOR_GRAY;
    // printf("Visit status of vetices %i is %d\n",u, G->color[u]);
    
    // printf("vertices %i with discovery time: %i\n", u, *time);

    // 3. for all 𝑦 ∈ adj[𝑥]
    // 4. if color[𝑦] == white
    // 5. 𝑝[𝑦] = 𝑥
    // 6. Visit(𝑦)
    List adjacencyList = G-> adjacencyList[u];
    moveFront(adjacencyList);

    while (index(adjacencyList) >= 0) {
        int v = get(adjacencyList);

        if (G->color[v] == COLOR_WHITE) {
            G->parent[v] = u;
            visit(G, v, S, time);
        }

        moveNext(adjacencyList);
    }
    // 7. color[𝑥] = black
    // 8. 𝑓[𝑥] = (+ + time) // finish 𝑥
    G->color[u] = COLOR_BLACK; // Mark the vertex as processed (black)
    G->finish[u] = ++(*time); // Record the finish time
    // printf("u: %i which is also the index needed to be deleted\n",u);
    int deleteIndex = -1;
    moveFront(S);
    // printList(stdout, S);
    // printf("\n");
    for (int i = 1; i <= length(S); i++) {
        if (get(S) == u) {
            // Store the index for deletion
            deleteIndex = index(S);
            break; // No need to continue searching
        }
        moveNext(S);
    }

    // Delete the marked element
    if (deleteIndex != -1) {
        moveFront(S);
        for (int i = 0; i < deleteIndex; i++) {
            moveNext(S);
        }
        // printList(stdout, S);
        // printf("\n");
        delete(S);
    }

    // Append u to the end of the list
    append(S, u);
    // printf("finish time: %i for vertices %i\n", *time, u);
}

/*
The second approach is to let
time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output
variable to Visit(). This is perhaps the simplest option, and is recommended.
*/

void DFS(Graph G, List S){
    /* Pre: length(S)==getOrder(G) */
    // 1. for all 𝑥 ∈ 𝑉(𝐺)
    // 2. color[𝑥] = white
    // 3. 𝑝[𝑥] = nil
    // 4. time = 0
    // 5. for all 𝑥 ∈ 𝑉(𝐺)
    // 6. if color[𝑥] == white
    // 7. Visit(𝑥
    if (length(S) != getOrder(G)) {
        printf("DFS precondtion not fulfiled length(S)==getOrder(G)");
        exit(EXIT_FAILURE);
    }
    // Initialize color array, parent array, and time
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = COLOR_WHITE;
        G->parent[i] = NIL;
    }

    // Creating local static variable in DFS for tracking time DFS and pass it into visit()
    int time = 0;
    moveFront(S);
    for (int i = 1; i <= getOrder(G); i ++){
        if(G->color[i] == COLOR_WHITE) {
            // printf("Will be vising %d with time %i\n", G->color[n], time);
            visit(G, i, S, &time);
        }
    }
}


/*** Other operations ***/
Graph transpose(Graph G) {
    int n = getOrder(G); // Number of vertices in the original graph
    Graph transposedGraph = newGraph(n); // Create a new graph with the same number of vertices

    // Iterate through each vertex in the original graph
    for (int u = 1; u <= n; u++) {
        List adjacencyList = G->adjacencyList[u];
        
        // Iterate through the neighbors of the current vertex in the original graph
        moveFront(adjacencyList);
        while (index(adjacencyList) >= 0) {
            int v = get(adjacencyList);
            
            // Add an edge from v to u in the transposed graph
            addArc(transposedGraph, v, u);

            moveNext(adjacencyList);
        }
    }
    return transposedGraph;
}

Graph copyGraph(Graph G) {
    if (G == NULL) {
        return NULL; // Handle NULL input graph
    }
    // Create a new graph with the same number of vertices
    Graph copy = newGraph(getOrder(G));

    // Iterate through vertices and edges in the original graph
    for (int i = 1; i <= getOrder(G); i++) {
        List originalAdjList = G->adjacencyList[i];
        moveFront(originalAdjList);

        // Iterate through the adjacency list of each vertex
        while (index(originalAdjList) >= 0) {
            int neighbor = get(originalAdjList);
            
            // Add directed edge to the new graph
            addArc(copy, i, neighbor);
            moveNext(originalAdjList);
        }
    }
    return copy;
}


void printGraph(FILE* out , Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        List adjacencyList = G->adjacencyList[i];
        moveFront(adjacencyList);
        while (index(adjacencyList)>= 0) {
            int v = get(adjacencyList);
            fprintf(out, "%d ", v);
            moveNext(adjacencyList);
        }
        fprintf(out,"\n");
    }
}


void FindSCC (Graph G, FILE* outputFile) {
    List L = newList();
    int b = getOrder(G);
    for (int i = 1; i <= b; i ++) {
        append(L, i);
    }
    // printf("Order of G : %i\n", b);
    DFS(G, L);
    // printf("before transposing: ");
    // printList(stdout, L);
    // printf("\n");
    // Now we transpose graph G and compute DFS with a output of a reverse List with DFS
    Graph GTA = transpose(G);
    // fprintf(outputFile, "Trans Graph:\n");
    // printGraph(outputFile, GTA);
    List gta = newList();
    for (int i = 1; i <= b; i ++) {
        append(gta, i);
    }
    // printList(stdout, gta);
    DFS(GTA, gta);
    // printf("after transposing: ");
    // printList(stdout, gta);
    // printf("\n");
    // printGraph(stdout, GTA);
    // printf("\n");
    int numberOfNILparent = 0;
    // printf("Order of GTA: %i", getOrder(GTA));
    for (int i = 1; i <= getOrder(GTA); i++) {
        if (GTA->parent[i] == 0) {
            // printf("GTA->parent[%i] is %i\n", i, GTA->parent[i]);
            numberOfNILparent++;
        }
    }
    // printf("number of parent: %i\n",numberOfNILparent);
    fprintf(outputFile, "G contains %i strongly connected componnets:", numberOfNILparent);
    int u;
    // int currentParent = NIL;
    moveBack(gta);
    int indexNo = 0;
    while (index(gta) >= 0) {
        u = get(gta);

        if (GTA->parent[u] == NIL) {
            // Mark the beginning of a new strong component
            indexNo++;
            fprintf(outputFile,"\n");
            fprintf(outputFile,"Component %i: ", indexNo);
        }
        fprintf(outputFile, "%d ", u);
        // Check if the parent changes, indicating the end of a strong component
        movePrev(gta);
    }
    // Print a newline at the end in case the last strong component is not followed by a new one
    fprintf(outputFile,"\n");
    freeList(&L);
    freeList(&gta);
    freeGraph(&GTA);
}






