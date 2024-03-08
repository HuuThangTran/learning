#include <stdio.h>
#include "Graph.h"

// Function to print the contents of a list
void printListContents(List L) {
    if (length(L) == 0) {
        printf("Empty\n");
        return;
    }
    moveFront(L);
    while (index(L) >= 0) {
        printf("%d ", get(L));
        moveNext(L);
    }
    printf("\n");
}

int main() {
    // Create a new graph with 8 vertices
    Graph G = newGraph(8);

    // Add edges to the graph
    addEdge(G, 1, 2);
    addEdge(G, 1, 5);
    addEdge(G, 2, 3);
    addEdge(G, 2, 5);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 6, 7);
    addEdge(G, 7, 8);

    // Perform DFS on the graph
    List S = newList();
    DFS(G, S);

    // Print the resulting components
    printf("Components:\n");
    moveBack(S);
    int component = 1;
    while (index(S) >= 0) {
        printf("Component %d:", component++);
        int vertex = get(S);
        movePrev(S);
        while (index(S) >= 0 && getParent(G, get(S)) == vertex) {
            printf(" %d", get(S));
            movePrev(S);
        }
        printf(" %d\n", vertex);
    }
    printf("\n");

    // Print the transposed graph
    printf("Transposed Graph:\n");
    Graph transposedG = transpose(G);
    printGraph(stdout, transposedG);
    printf("\n");

    // Copy the graph
    Graph copyG = copyGraph(G);
    printf("Copied Graph:\n");
    printGraph(stdout, copyG);
    printf("\n");

    // Test access functions
    printf("Order of G: %d\n", getOrder(G));
    printf("Size of G: %d\n", getSize(G));
    printf("Parent of vertex 3: %d\n", getParent(G, 3));
    printf("Discover time of vertex 4: %d\n", getDiscover(G, 4));
    printf("Finish time of vertex 5: %d\n\n", getFinish(G, 5));

    // Free memory allocated for the graphs
    freeGraph(&G);
    freeGraph(&transposedG);
    freeGraph(&copyG);

    return 0;
}