#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "DFS.h"
#include "SGH.h"

#define MAX_VERTICES 100  // Maximum number of vertices in a graph

void initializeGraph(Graph *g, int numVertices) {
    if (g == NULL) {
        printf("Error: Graph is NULL.\n");
        exit(1);
    }

    g->numVertices = numVertices;

    g->adjacencyMatrix = allocateMatrix(numVertices, numVertices);
    if (g->adjacencyMatrix == NULL) {
        printf("Error: Unable to allocate adjacency matrix.\n");
        exit(1);
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int src, int dest) {
    g->adjacencyMatrix[src][dest] = 1;
    g->adjacencyMatrix[dest][src] = 1; // For undirected graph
}


void modularProduct(const Graph *g1, const Graph *g2, Graph *result) {
    
    int numVertices = g1->numVertices * g2->numVertices;
    initializeGraph(result, numVertices);

    for (int i = 0; i < g1->numVertices; i++) {
        for (int j = 0; j < g2->numVertices; j++) {
            for (int k = 0; k < g1->numVertices; k++) {
                for (int l = 0; l < g2->numVertices; l++) {
                    if ((g1->adjacencyMatrix[i][k] == g2->adjacencyMatrix[j][l]) &&
                (g1->adjacencyMatrix[i][k] == 1 || g1->adjacencyMatrix[k][i] == 0) &&
                (g2->adjacencyMatrix[j][l] == 1 || g2->adjacencyMatrix[l][j] == 0)) {
                addEdge(result, i * g2->numVertices + j, k * g2->numVertices + l);
                }
            }
            }
        }
    }
}




