#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//calculate the size of the graph: |V| + |E|
int calculateGraphSize(Graph* graph) {
    int numVertices = graph->numVertices;
    int numEdges = 0;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (graph->adjacencyMatrix[i][j] == 1) {
                numEdges++;
            }
        }
    }

    int graphSize = numVertices + numEdges/2;
    return graphSize;
}

void partA(Graph* graph) {
    int graphSize = calculateGraphSize(graph);
    printf("Graph size: %d\n", graphSize);
}
