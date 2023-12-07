#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "metric.h"
// #include "DFS.h"
//#include "SGH.h"
#include "MCS.h"
#include <time.h>
//#include "MCSplit.h"

void printAdjacencyMatrix(const Graph *g) {
    printf("Adjacency Matrix of Modular Product Graph:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

// free memory`
void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
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

// tool for PartC
void partC(Graph *graph)
{
    clock_t start, end;
    start = clock();
    printf("The results by SequantialGreedyHeuristicSearchAlgorithm(approximate approach). \n");
    SGHA_findClique(graph->adjacencyMatrix, graph->numVertices);
    end = clock();
    printf("Program SGHA_findClique %f seconds to execute\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    start = clock();
    printf("The results by DFS(precise approach).\n");
    DFS_mainFunction(graph->adjacencyMatrix, graph->numVertices);
    end = clock();
    printf("Program DFS_mainFunction %f seconds to execute\n", ((double)(end - start)) / CLOCKS_PER_SEC);
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

void partD(Graph *g1, Graph *g2) {
    printf("\nMaximum Common Subgraph (MCS)\n");
    Graph *result = (Graph *)malloc(sizeof(Graph));  // Allocate memory for the result graph
    if (result == NULL) {
        printf("Error allocating memory for the result graph.\n");
        // Handle memory allocation error, such as by exiting the program
        exit(1);
    }
    modularProduct(g1, g2, result);
    printf("Number of Vertices: %d\n", result->numVertices);
    printAdjacencyMatrix(result);
    //DFS_mainFunction(result->adjacencyMatrix, result->numVertices);
    SGHA_findClique(result->adjacencyMatrix, result->numVertices);
    freeGraph(result);
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    FILE *file2 = fopen("input2.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int numGraphs;
    fscanf(file, "%d", &numGraphs);

    for (int i = 0; i < numGraphs; i++)
    {

        printf("\n#######################################################\n");
        Graph *graph = readGraphFromFile(file);

        showInputGraph(graph, i);
        printf("\n-------------------------------------------------------\n");
        // Liu's part
        partB(graph);
        printf("\n-------------------------------------------------------\n");
        // Wen's part
        partC(graph);
        printf("\n-------------------------------------------------------\n");
        
        printf("\n#######################################################\n");
    }
    // Mevin's part
    Graph *graph1 = readGraphFromFile(file2);

    // showInputGraph(graph1, 0);

    Graph *graph2 = readGraphFromFile(file2);

    // showInputGraph(graph2, 1);

    Graph *graph3 = readGraphFromFile(file2);

    // showInputGraph(graph3, 2);

    Graph *graph4 = readGraphFromFile(file2);

    // showInputGraph(graph4, 3);

    Graph *graph5 = readGraphFromFile(file2);

    // showInputGraph(graph5, 4);

    Graph *graph6 = readGraphFromFile(file2);

    // showInputGraph(graph6, 5);

    //OUTPUT                       //DFS            //SGH
    partD(graph1, graph2);      //(Works)      //(Hangs Infinitely)
    // partD(graph1, graph3);      //(Works)      //(Hangs Infinitely)
    // partD(graph2, graph3);  //(Exception)   //(Hangs Infinitely)
    // partD(graph1, graph4);     //(Works)       /(Hangs Infinitely)
    // partD(graph1, graph5);     //(Works)       //(Hangs Infinitely) 
    // partD(graph1, graph6);     //(Works)        //(Hangs Infinitely) 
    // partD(graph2, graph4);     //(Works)       //(Hangs Infinitely) 
    // partD(graph2, graph5);  //(Exception)   //(Hangs Infinitely)
    // partD(graph2, graph6);     //(Works)       //(Hangs Infinitely) 
    // partD(graph3, graph4);     //(Works)       //(Hangs Infinitely) 
    // partD(graph3, graph5);     //(Works)       //(Hangs Infinitely) 
    // partD(graph3, graph6);     //(Works)         //(Hangs Infinitely) 
    // partD(graph4, graph5); //(Hangs Infinitely)  //(Hangs Infinitely)
    // partD(graph4, graph6); //(Hangs Infinitely)  //(Hangs Infinitely)
    // partD(graph5, graph6); //(Hangs Infinitely) //(Hangs Infinitely)


    freeGraph(graph1);
    freeGraph(graph2);
    freeGraph(graph3); 
    freeGraph(graph4);
    freeGraph(graph5);
    freeGraph(graph6);
    fclose(file);
    return 0;
}
