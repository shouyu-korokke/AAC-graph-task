#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "metric.h"
#include "DFS.h"
#include "SGH.h"
#include <time.h>

// allocate memory
int **allocateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// free memory
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
    printf("Program SGHA_findClique %f seconds to execute\n", ((double)(end - start)) / CLOCKS_PER_SEC);
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


int main()
{
    FILE *file = fopen("input.txt", "r");
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
        // Mevin's part
        //partD(graph);
        printf("\n#######################################################\n");
    }

    fclose(file);
    return 0;
}
