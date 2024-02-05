/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* README.md // FileName
* Graph.h Private and hide the the fucntion from Graph.c to the user and create and define a header file // Describe the program
***/

#include "Graph.h"
#include <stdio.h>
#include "List.h"

// for int main void
#include <stdlib.h>


#define COLOR_WHITE ((char)0)
#define COLOR_GRAY  ((char)1)
#define COLOR_BLACK ((char)2)



// for int main void
#define MAX_LINE_LENGTH 100



struct GraphObj {
    /*
• An array of Lists whose ith element contains the neighbors of vertex i.
• An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i.
• An array of ints whose ith element is the parent of vertex i.
• An array of ints whose ith element is the distance from the (most recent) source to vertex i.
You should also include fields storing the number of vertices (called the order of the graph), the number of
edges (called the size of the graph), and the label of the vertex that was most recently used as source for
BFS. It is recommended that all arrays be of length 𝑛 + 1, where 𝑛 is the number of vertices in the graph,
and that only indices 1 through n be used. This is so that array indices can be directly identified with vertex
labels
    */
    // An array of Lists whose ith element contains the neighbors of vertex i.
    List* adjacencyList;
    // An array of ints (or chars, or strings) whose ith element is the color (white, gray, black) of vertex i.
    char* color;
    // An array of ints whose ith element is the parent of vertex i.
    int* parent; 
    // An array of ints whose ith element is the distance from the (most recent) source to vertex i.
    int* distance;
    // You should also include fields storing the number of vertices (called the order of the graph)
    int order;
    // the number of edges (called the size of the graph)
    int size;
    int* discovery;
    int* finish;
};

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

//Pa2
// int getSource (Graph G) {
//     return G->source;
// }
// pa2
// int getDist   (Graph G, int u) {

// }
// pa2
// void getPath   (List L, Graph G, int u) {
    
// }

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
    return G->parent[u];
}
int getFinish(Graph G, int u) {
    /* Pre: 1<=u<=n=getOrder(G) */ 
    if (u < 1 || u > getOrder(G)) {
    printf("getDiscorver ERROR: u < 1 || u > G->getOrder()\n");
    exit(EXIT_FAILURE);
    }
    return G->parent[u];
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
    insertVertices(G,v,u);
    G->size ++;
}

// helper function for DFS
void visit(Graph G, int u, List S, int time) {
    G->color[u] = COLOR_GRAY;
    printf("time: %i", time);
    G->discovery[u] = ++time;
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

    G->color[u] = COLOR_BLACK; // Mark the vertex as processed (black)
    G->finish[u] = ++time; // Record the finish time
    prepend(S, u); // Store the vertex in the List S (considered as a stack)
}

/*
The second approach is to let
time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output
variable to Visit(). This is perhaps the simplest option, and is recommended.
*/

void DFS(Graph G, List S){
    /* Pre: length(S)==getOrder(G) */
    if (length(S) != getOrder(G)) {
        printf("DFS precondtion not fulfiled length(S)==getOrder(G)");
    }

    // Creating local static variable in DFS for tracking time DFS and pass it into visit()
    static int time = 0;

    moveFront(S);
    while(index(S) >= 0) {
        int n = get(S);
        if(G->color[n] == COLOR_WHITE) {
            visit(G, n, S, time);
        }
        moveNext(S);
    }


} 


/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);


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
    printf("The number of line: %i\n", line);

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
    printf("Order: %i\n", G->order);
    printf("The nubmer of vertices: %i\n", numVertices);

    // Reading the next folliwing lines for vertices sources and their destination to implement edges
    int src, dest;
    while (fscanf(inputFile, "%d %d", &src, &dest) == 2 && (src != 0 && dest != 0)) {
        // Print the line
        addArc(G, src, dest);
        printf("Read: %d, %d\n", src, dest);
    }
    // Print out the size to check Size: the number of edges
    printf("size: %i\n", G->size);

    // Print out to the ouput file, now printing to the terminal to check
    printf("Output:\nAdjacency list representation of G:\n");
    printGraph(stdout,G);
    fprintf(outputFile, "Output:\nAdjacency list representation of G:\n");
    printGraph(outputFile, G);


}

