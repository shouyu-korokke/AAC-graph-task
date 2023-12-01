#include <stdio.h>
#include <stdlib.h>
#include "graph.c" // Include the graph.c file for graph definitions and functions

typedef struct
{
    int numVertices;
    int **adjacencyMatrix;
} Subgraph;

Subgraph *createSubgraph(Graph *graph, int numVertices) {
    Subgraph *subgraph = (Subgraph *)malloc(sizeof(Subgraph));
    subgraph->numVertices = numVertices;
    subgraph->adjacencyMatrix = allocateMatrix(subgraph->numVertices, subgraph->numVertices);

    printf("Creating subgraph with %d vertices.\n", numVertices);
    for (int i = 0; i < subgraph->numVertices; i++) {
        for (int j = 0; j < subgraph->numVertices; j++) {
            subgraph->adjacencyMatrix[i][j] = graph->adjacencyMatrix[i][j];
            printf("%d ", subgraph->adjacencyMatrix[i][j]); // Debug print
        }
        printf("\n");
    }

    return subgraph;
}


void freeSubgraph(Subgraph *subgraph)
{
    freeMatrix(subgraph->adjacencyMatrix, subgraph->numVertices);
    free(subgraph);
}

int isSubgraph(Subgraph *subgraph, Graph *graph)
{
    for (int i = 0; i < subgraph->numVertices; i++)
    {
        for (int j = 0; j < subgraph->numVertices; j++)
        {
            if (subgraph->adjacencyMatrix[i][j] == 1 && graph->adjacencyMatrix[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int isCommonSubgraph(Subgraph *subgraph1, Subgraph *subgraph2) {
    if (subgraph1->numVertices != subgraph2->numVertices) {
        return 0;
    }
    for (int i = 0; i < subgraph1->numVertices; i++) {
        for (int j = 0; j < subgraph1->numVertices; j++) {
            if (subgraph1->adjacencyMatrix[i][j] != subgraph2->adjacencyMatrix[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int calculateMCSSize(Subgraph *subgraph) {
    return subgraph->numVertices;
}

Subgraph *MCS(Graph *graph1, Graph *graph2) {
    int minNumVertices = (graph1->numVertices < graph2->numVertices) ? graph1->numVertices : graph2->numVertices;
    Subgraph *maxMCS = (Subgraph *)malloc(sizeof(Subgraph));
    maxMCS->numVertices = minNumVertices;
    maxMCS->adjacencyMatrix = allocateMatrix(minNumVertices, minNumVertices);

    for (int i = 0; i < minNumVertices; i++) {
        for (int j = 0; j < minNumVertices; j++) {
            maxMCS->adjacencyMatrix[i][j] = (i == j) ? 1 : 0;
        }
    }

    return maxMCS;
}


int main() {
       printf("Starting the program...\n");

    FILE *file1 = fopen("g1.txt", "r");
    if (file1 == NULL) {
        perror("Error opening g1.txt");
        return 1;
    }

    FILE *file2 = fopen("g2.txt", "r");
    if (file2 == NULL) {
        perror("Error opening g2.txt");
        fclose(file1); // Close file1 before exiting
        return 1;
    }

    printf("Files opened successfully.\n");

    printf("Reading the first graph...\n");
    
    // Read the first graph
    Graph *graph1 = readGraphFromFile(file1);
    if (graph1 == NULL) {
        fprintf(stderr, "Failed to read the first graph.\n");
        fclose(file1);
        return 1;
    }

    printf("Reading the second graph...\n");

    // Read the second graph
    Graph *graph2 = readGraphFromFile(file2);
    if (graph2 == NULL) {
        fprintf(stderr, "Failed to read the second graph.\n");
        freeGraph(graph1); // Free the first graph before exiting
        fclose(file2);
        return 1;
    }

    // Now that we have both graphs, we can find their MCS
    Subgraph *mcs = MCS(graph1, graph2);

    // Print the MCS
    if (mcs != NULL) {
        printf("MCS Number of Vertices: %d\n", mcs->numVertices);
        printf("MCS Adjacency Matrix: ");
        for (int row = 0; row < mcs->numVertices; row++) {
            for (int col = 0; col < mcs->numVertices; col++) {
                printf("%d ", mcs->adjacencyMatrix[row][col]);
            }
            printf("\n");
        }
        freeSubgraph(mcs); // Don't forget to free the MCS subgraph
    } else {
        printf("No MCS found.\n");
    }

    // Free the memory for both graphs
    freeGraph(graph1);
    freeGraph(graph2);

    fclose(file1);
    fclose(file2);
    return 0;
}