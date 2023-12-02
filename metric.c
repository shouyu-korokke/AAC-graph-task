#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 100
int allSubsets[MAX_VERTICES][MAX_VERTICES];

int subsetCount = 0;
int minResolvingSet[MAX_VERTICES];
int minResolvingSetSize = INT_MAX;


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct {
    Node* head;
} AdjList;


typedef struct {
    int numVertices;
    AdjList* array;
} Graph;


Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));

    for (int i = 0; i < vertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}


void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;


}

// BFS algorithm to calculate distance
int calculateDistance(Graph* graph, int start, int end) {
    if (start == end) {
        return 0;
    }

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    int* distance = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        distance[i] = -1;
    }

    visited[start] = 1;
    distance[start] = 0;

    int queue[MAX_VERTICES];
    int front = -1, rear = -1;
    queue[++rear] = start;

    while (front != rear) {
        int current = queue[++front];

        Node* temp = graph->array[current].head;
        while (temp) {
            int adjacentVertex = temp->vertex;

            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = 1;
                distance[adjacentVertex] = distance[current] + 1;
                queue[++rear] = adjacentVertex;

                if (adjacentVertex == end) {
                    int res = distance[adjacentVertex];
                    free(visited);
                    free(distance);
                    return res;
                }
            }

            temp = temp->next;
        }
    }

    free(visited);
    free(distance);

    return -1;
}



void printSubsets(int subset[], int subsetSize) {
    for (int i = 0; i < subsetSize; i++) {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

void storeSubset(int subset[], int subsetSize) {
    for (int i = 0; i < subsetSize; i++) {
        allSubsets[subsetCount][i] = subset[i];
    }
    // store element to allSubsets
    allSubsets[subsetCount][subsetSize] = -1;  
    subsetCount++;
}

//backtraking algorithm to find all subsets of graph array
void calcSubset(int A[], int n, int subset[], int subsetSize, int index) {
    //printSubsets(subset, subsetSize);
    storeSubset(subset, subsetSize);
    for (int i = index; i < n; i++) {
        subset[subsetSize] = A[i];
        calcSubset(A, n, subset, subsetSize + 1, i + 1);
    }
}

void subsets(int A[], int n) {
    int* subset = (int*)malloc(MAX_VERTICES * sizeof(int));
    calcSubset(A, n, subset, 0, 0);
    free(subset);
}

// Check if the given subset is a resolving set for the graph
bool isSubsetResolving(Graph* graph, int subset[], int subsetSize) {
    // 遍历所有顶点，检查子集是否可以解析每个顶点

    int* dist_i = (int*)malloc(subsetSize * sizeof(int));
    int* dist_j = (int*)malloc(subsetSize * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        bool isUnique = true;
        for (int j = 0; j < graph->numVertices && isUnique; j++) {
            if (i != j) {
                for (int k = 0; k < subsetSize; k++) {
                    dist_i[k] = calculateDistance(graph, i, subset[k]);
                    dist_j[k] = calculateDistance(graph, j, subset[k]);
                }
                isUnique = !isUnique || memcmp(dist_i, dist_j, subsetSize * sizeof(int)) != 0;
            }
        }
        if (!isUnique) {
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
void findResolvingSets(Graph* graph) {
    printf("Resolving sets\n");
    for (int i = 0; i < subsetCount; i++) {
        int j = 0;
        // calculate the size of current subsets
        while (allSubsets[i][j] != -1 && j < graph->numVertices) {
            j++;
        }
        if (isSubsetResolving(graph, allSubsets[i], j)) {
            //printSubsets(allSubsets[i], j);
            minResolvingSetSize = j;
            memcpy(minResolvingSet, allSubsets[i], j * sizeof(int));
        }
    }
    
}


int main() {

    FILE *file = fopen("input.txt","r");
    if (file == NULL)
    {
        perror("File open");
    }
    //int vertices, edges;
    int vertexNum;
    /*while (fscanf(file, "%d", &vertexNum) != EOF)
    {
        Graph* graph = createGraph(vertexNum);
        int src, dest;
        for (int i = 0; i < vertexNum - 1; i++)
        {
            if (fscanf(file, "%d %d", &src, &dest) != EOF)
            {
                addEdge(graph, src, dest);
            }
            int vertices[MAX_VERTICES];
            for (int j= 0; j < graph->numVertices; j++)
            {
                vertices[j] = j;
            }
            subsets(vertices, graph->numVertices);
            findResolvingSets(graph);
            for (int k = 0; k < minResolvingSetSize; k++)
            {
                printf("%d ", minResolvingSet[k]);
            }
            printf("\n");
            printf("\nSize: %d\n", minResolvingSetSize);
            
        }

    }*/
    fscanf(file, "%d", &vertexNum);
    int src, dest;
    Graph* graph = createGraph(vertexNum);
    while (fscanf(file, "%d %d", &src, &dest) != EOF)
    {
        addEdge(graph, src, dest);   
    }
    int vertices[MAX_VERTICES];
    for (int i = 0; i < graph->numVertices; i++) {
        vertices[i] = i;
    }


    subsets(vertices, graph->numVertices);
    //resolving sets
    findResolvingSets(graph);
    for (int i = 0; i < minResolvingSetSize; i++)
    {
        printf("%d ", minResolvingSet[i]);
    }
    printf("\nSize: %d\n", minResolvingSetSize);

    printf("end\n");
    fclose(file);




    return 0;
}
