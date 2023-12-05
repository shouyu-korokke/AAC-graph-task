#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "DFS.h"

#define MAX_VERTICES 100  // Maximum number of vertices in a graph

// free memory
void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

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

    printf("Modular Product Computation Started\n");
    for (int i = 0; i < g1->numVertices; i++) {
        for (int j = 0; j < g2->numVertices; j++) {
            for (int k = 0; k < g1->numVertices; k++) {
                for (int l = 0; l < g2->numVertices; l++) {
                    if ((g1->adjacencyMatrix[i][k] == g2->adjacencyMatrix[j][l]) &&
                (g1->adjacencyMatrix[i][k] == 1 || g1->adjacencyMatrix[k][i] == 0) &&
                (g2->adjacencyMatrix[j][l] == 1 || g2->adjacencyMatrix[l][j] == 0)) {
                addEdge(result, i * g2->numVertices + j, k * g2->numVertices + l);
                printf("Edge added between (%d, %d) and (%d, %d)\n", i, j, k, l);
            }
                else {
                        printf("No edge added for (%d, %d) and (%d, %d)\n", i, j, k, l);
                    }
                }
            }
        }
    }
    printf("Modular Product Computation Completed\n");
}


void freeGraph(Graph *graph)
{
    freeMatrix(graph->adjacencyMatrix, graph->numVertices);
    free(graph);
}

// read a graph
Graph *readGraphFromFile(FILE *file)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    fscanf(file, "%d", &graph->numVertices);
    graph->adjacencyMatrix = allocateMatrix(graph->numVertices, graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            fscanf(file, "%d", &graph->adjacencyMatrix[i][j]);
        }
    }

    // add code here if additional info needed

    return graph;
}



void MCS_DFS(int **adjMatrix, int graphVertix)
{
    // Malloc variables
    int *temp_cs = (int *)malloc(graphVertix * sizeof(int));

    int **max_cs = (int **)malloc(graphVertix * sizeof(int *));
    for (int i = 0; i < graphVertix; i++) {
        max_cs[i] = (int *)malloc(graphVertix * sizeof(int));
    }
    // initialize variables
    int num_max_cs = 0;
    int max_size = 0;

    //main program
    DFS_findMaxCliques(-1, 0, temp_cs, max_cs, &num_max_cs, &max_size, adjMatrix, graphVertix);

    printf("Total Number of Maximum Common Subgraphs: %d\n", num_max_cs);
    for (int i = 0; i < num_max_cs; i++) {
        printf("Maximum Common Subgraph %d: ", i + 1);
        printClique(max_cs[i], max_size);
        DFS_printMatrixWithClique(adjMatrix, max_cs[i], max_size, i, graphVertix);
    }
}

void printAdjacencyMatrix(const Graph *g) {
    printf("Adjacency Matrix of Modular Product Graph:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}
void showInputGraph(Graph *graph, int i)
{

    printf("Graph no.%d:\n", i + 1);
    printf("Number of Vertices: %d\n", graph->numVertices);

    // Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int row = 0; row < graph->numVertices; row++)
    {
        for (int col = 0; col < graph->numVertices; col++)
        {
            printf("%d ", graph->adjacencyMatrix[row][col]);
        }
        printf("\n");
    }
}

int main1() {
    FILE *file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Graph *graph1 = readGraphFromFile(file);

    showInputGraph(graph1, 0);

    Graph *graph2 = readGraphFromFile(file);

    showInputGraph(graph2, 1);

    Graph *graph3 = readGraphFromFile(file);

    showInputGraph(graph3, 2);

    // Example: Processing modular product for first two graphs
    Graph *result = (Graph *)malloc(sizeof(Graph));  // Allocate memory for the result graph
    if (result == NULL) {
        printf("Error allocating memory for the result graph.\n");
        // Handle memory allocation error, such as by exiting the program
        exit(1);
    }
    initializeGraph(result, graph1->numVertices * graph2->numVertices);
    modularProduct(graph1, graph2, result);
    printf("Adjacency Matrix of Modular Product (Graph 1 and Graph 2):\n");
    printAdjacencyMatrix(result);
    freeGraph(result);

    // Don't forget to free the memory allocated for graphs
    freeGraph(graph1);
    freeGraph(graph2);
    freeGraph(graph3);

    fclose(file);
    return 0;
}
