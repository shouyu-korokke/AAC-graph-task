#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numVertices;
    int **adjacencyMatrix;
    // add more fields as needed
} Graph;



//allocate memory
int **allocateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

//free memory
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


//read a graph
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

    //add code here if additional info needed

    return graph;
}

int main()
{
    //open file
    FILE *file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int numGraphs;
    fscanf(file, "%d", &numGraphs);

    for (int i = 0; i < numGraphs; i++)
    {
        Graph *graph = readGraphFromFile(file);

        ///-----------FOR TESTING-----------///
        printf("Graph %d:\n", i + 1);
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
        ///-----------FOR TESTING-----------///


        //TODO

        printf("\n");
        freeGraph(graph);
    }

    fclose(file);
    return 0;
}
