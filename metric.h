
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

#define MAX_VERTICES 100
int allSubsets[MAX_VERTICES][MAX_VERTICES];

int subsetCount = 0;
int minResolvingSet[MAX_VERTICES];
int minResolvingSetSize = INT_MAX;

// BFS algorithm to calculate distance
int calculateDistance(Graph *graph, int start, int end)
{
    if (start == end)
    {
        return 0;
    }

    int *visited = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = 0;
    }

    int *distance = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        distance[i] = -1;
    }

    visited[start] = 1;
    distance[start] = 0;

    int queue[MAX_VERTICES];
    int front = -1, rear = -1;
    queue[++rear] = start;

    while (front != rear)
    {
        int current = queue[++front];

        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjacencyMatrix[current][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                queue[++rear] = i;

                if (i == end)
                {
                    int res = distance[i];
                    free(visited);
                    free(distance);
                    return res;
                }
            }
        }
    }

    free(visited);
    free(distance);

    return -1;
}

void printSubsets(int subset[], int subsetSize)
{
    for (int i = 0; i < subsetSize; i++)
    {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

void storeSubset(int subset[], int subsetSize)
{
    for (int i = 0; i < subsetSize; i++)
    {
        allSubsets[subsetCount][i] = subset[i];
    }
    // store element to allSubsets
    allSubsets[subsetCount][subsetSize] = -1;
    subsetCount++;
}

// backtraking algorithm to find all subsets of graph array
void calcSubset(int A[], int n, int subset[], int subsetSize, int index)
{
    // printSubsets(subset, subsetSize);
    storeSubset(subset, subsetSize);
    for (int i = index; i < n; i++)
    {
        subset[subsetSize] = A[i];
        calcSubset(A, n, subset, subsetSize + 1, i + 1);
    }
}
// helper function for calcSubset
void subsets(int A[], int n)
{
    int *subset = (int *)malloc(MAX_VERTICES * sizeof(int));
    calcSubset(A, n, subset, 0, 0);
    free(subset);
}

// Check if the given subset is a resolving set for the graph
bool isSubsetResolving(Graph *graph, int subset[], int subsetSize)
{

    int *dist_i = (int *)malloc(subsetSize * sizeof(int));
    int *dist_j = (int *)malloc(subsetSize * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++)
    {
        bool isUnique = true;
        for (int j = 0; j < graph->numVertices && isUnique; j++)
        {
            if (i != j)
            {
                for (int k = 0; k < subsetSize; k++)
                {
                    dist_i[k] = calculateDistance(graph, i, subset[k]);
                    dist_j[k] = calculateDistance(graph, j, subset[k]);
                }
                isUnique = !isUnique || memcmp(dist_i, dist_j, subsetSize * sizeof(int)) != 0;
            }
        }
        if (!isUnique)
        {
            free(dist_i);
            free(dist_j);
            return false;
        }
    }

    free(dist_i);
    free(dist_j);
    return true;
}

// Logic to generate all subsets and check if they are resolving sets
void findResolvingMinimalSets(Graph *graph)
{
    printf("Resolving sets\n");
    for (int i = 0; i < subsetCount; i++)
    {
        int j = 0;
        // calculate the size of current subsets
        while (allSubsets[i][j] != -1 && j < graph->numVertices)
        {
            j++;
        }
        if (isSubsetResolving(graph, allSubsets[i], j))
        {
            // printSubsets(allSubsets[i], j);
            minResolvingSetSize = j;
            memcpy(minResolvingSet, allSubsets[i], j * sizeof(int));
        }
    }
}
// Reset all global variables
void resetGlobals()
{
    subsetCount = 0;
    minResolvingSetSize = INT_MAX;
    memset(minResolvingSet, 0, sizeof(minResolvingSet));
}

void partB(Graph *graph)
{
    //  declare a graph array
    int vertices[MAX_VERTICES];
    for (int n = 0; n < graph->numVertices; n++)
    {
        vertices[n] = n;
    }
    // find its all subsets
    subsets(vertices, graph->numVertices);
    //
    findResolvingMinimalSets(graph);
    // print metric size
    printf("\nMetric Size: %d\n", minResolvingSetSize);
    printf("\n");
}