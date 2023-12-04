#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>


// void color(short x)	//change colour according to the parameters
// {
//     if(x>=0 && x<=15)//parameters in range 0-15
//     	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//Only one parameter for changing word colour 
//     else//default white
//     	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
// }


void printMatrixWithClique(int** adjMatrix, bool* clique, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (clique[i] && clique[j]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
            }
            printf("%d ", adjMatrix[i][j]);
            if (clique[i] && clique[j]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }
        }
        printf("\n");
    }
}

void InitialGraph(int** adjMatrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    // adjMatrix[0][1] = 1; adjMatrix[1][0] = 1;
    // adjMatrix[3][0] = 1; adjMatrix[0][3] = 1;
    // adjMatrix[1][2] = 1; adjMatrix[2][1] = 1;
    // adjMatrix[0][2] = 1; adjMatrix[2][0] = 1;
    // adjMatrix[1][3] = 1; adjMatrix[3][1] = 1;
    // adjMatrix[1][4] = 1; adjMatrix[4][1] = 1;
    // adjMatrix[3][2] = 1; adjMatrix[2][3] = 1;
    // adjMatrix[2][4] = 1; adjMatrix[4][2] = 1;
    // adjMatrix[3][4] = 1; adjMatrix[4][3] = 1; 
    // (0, 1, 2, 3) (1, 2, 3, 4)
    adjMatrix[0][1] = 1; adjMatrix[1][0] = 1;
    adjMatrix[0][2] = 1; adjMatrix[2][0] = 1;
    adjMatrix[1][2] = 1; adjMatrix[2][1] = 1;
    adjMatrix[3][4] = 1; adjMatrix[4][3] = 1;
    // (0, 1, 2)
    // adjMatrix[0][2] = 1; adjMatrix[2][0] = 1;
    // adjMatrix[0][3] = 1; adjMatrix[3][0] = 1;
    // adjMatrix[0][4] = 1; adjMatrix[4][0] = 1;
    // adjMatrix[1][2] = 1; adjMatrix[2][1] = 1;
    // adjMatrix[3][4] = 1; adjMatrix[4][3] = 1;
    // (0, 3, 4)
}

// find the Max Degree Vertex
int findMaxDegreeVertex(int** adjMatrix, bool* included, int N) {
    int maxDegree = -1, maxIndex = -1;
    for (int v = 0; v < N; v++) {
        if (!included[v]) {
            int degree = 0;
            for (int i = 0; i < N; i++) {
                degree += adjMatrix[v][i];
            }
            if (degree > maxDegree) {
                maxDegree = degree;
                maxIndex = v;
            }
        }
    }
    return maxIndex;
}

// check if the vertices are connected with all vertices in the clique
bool canBeAddedToClique(int v, bool* clique, int** adjMatrix, int N) {
    for (int i = 0; i < N; i++) {
        if (clique[i] && !adjMatrix[v][i]) {
            return false;
        }
    }
    return true;
}

// Sequential Greedy Heuristic Search algorithm
void SGHA_findClique(int** adjMatrix, int N) {
    bool clique[N];
    bool included[N];
    for (int count = 0; count < N; count ++)
    {
        clique[count] = false;
    }

    for (int count = 0; count < N; count ++)
    {
        included[count] = false;
    }
    while (true) {
        int v = findMaxDegreeVertex(adjMatrix, included, N);
        if (v == -1) break;
        if (canBeAddedToClique(v, clique, adjMatrix, N)) {
            clique[v] = true;
            for (int i = 0; i < N; i++) {
                if (!adjMatrix[v][i]) included[i] = true;
            }
        } else {
            included[v] = true;
        }
    }

    // print vertices in the clique
    printf("Vertices in Clique: ");
    for (int i = 0; i < N; i++) {
        if (clique[i]) printf("%d ", i);
    }
    printf("\n");
    
    printMatrixWithClique(adjMatrix, clique, N);

}

// int main() {
//     int N;
//     N = 5;

//     int **adjMatrix = (int **)malloc(N * sizeof(int *));
//     for (int i = 0; i < N; i++) {
//         adjMatrix[i] = (int *)malloc(N * sizeof(int));
//         for (int j = 0; j < N; j++) {
//             adjMatrix[i][j] = i + j; 
//         }
//     }

//     InitialGraph(adjMatrix, N);
//     findClique(adjMatrix, N);
//     return 0;
// }
