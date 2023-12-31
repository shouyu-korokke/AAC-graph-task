#ifndef GRAPH_H
#define GRAPH_H

// Define a structure for a graph
typedef struct
{
    int numVertices;           // Number of vertices in the graph
    int **adjacencyMatrix;     // Pointer to a 2D array representing the adjacency matrix

} Graph;

// Function to allocate memory for a 2D matrix (adjacency matrix)
int **allocateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix; 
}


#endif