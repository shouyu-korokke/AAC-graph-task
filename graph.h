#ifndef GRAPH_H
#define GRAPH_H

typedef struct
{
    int numVertices;
    int **adjacencyMatrix;
    // add more fields as needed
} Graph;


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


#endif