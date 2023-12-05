#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

// void color(short x)	//change colour according to the parameters
// {
//     if(x>=0 && x<=15)//parameters in range 0-15
//     	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//Only one parameter for changing word colour 
//     else//default white
//     	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
// }

bool isInClique(int v, int* clique, int size) {
    for (int i = 0; i < size; i++) {
        if (clique[i] == v)
         {
            return true;
        }
    }
    return false;
}


void DFS_printMatrixWithClique(int** adjMatrix, int* clique, int size, int colorIndex, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isInClique(i, clique, size) && isInClique(j, clique, size)) {
                // The clique will be changed colour showing in console
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
            }
            printf("%d ", adjMatrix[i][j]);
            if (isInClique(i, clique, size) && isInClique(j, clique, size)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            }
        }
        printf("\n");
    }
}

//check the new vertex is connected to all vertices in the current clique.
bool isClique(int size, int* temp_clique, int** adjMatrix) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (adjMatrix[temp_clique[i]][temp_clique[j]] == 0) {
                return false;
            }
        }
    }
    return true;
}

void printClique(int* clique, int size) {
    printf("Clique: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", clique[i]);
    }
    printf("\n");
}

void DFS_findMaxCliques(int i, int size, int* temp_clique, int** max_cliques, int *num_max_cliques, int *max_size, int** adjMatrix, int N) {
       
    //check if the size of current clique is greater than max clique size.
    if (size == *max_size) {

        //The first clique print will be empty
        printClique(temp_clique, size); 

        for (int j = 0; j < size; j++) {
        // if there are multiple cliques, then they will be stored in the max_cliques[][]
            max_cliques[*num_max_cliques][j] = temp_clique[j];
        }
        //The number of maximal cliques
        (*num_max_cliques)++; 
    } 

    else if (size > *max_size) {
        *max_size = size;
        *num_max_cliques = 0;
        printClique(temp_clique, size); 
        for (int j = 0; j < size; j++) {
            max_cliques[0][j] = temp_clique[j];
        }
        *num_max_cliques = 1;
    }

    // The main part of DFS algorithm
    // i = -1 then j = 0; i is for count recursion; 
    // The initial size is 0, which will increase in the subsequent process.
    for (int j = i + 1; j < N; j++) {
        temp_clique[size] = j; //current vertex
        //if isNot a clique, then check the next vertex, until finishing check the last vertex.
        if (isClique(size + 1, temp_clique, adjMatrix)) {
            DFS_findMaxCliques(j, size + 1, temp_clique, max_cliques, num_max_cliques, max_size, adjMatrix, N);
        }
    }
}

//Start.
void DFS_mainFunction(int **adjMatrix, int graphVertix) {

    // Malloc variables
    int *temp_clique = (int *)malloc(graphVertix * sizeof(int));

    int **max_cliques = (int **)malloc(graphVertix * sizeof(int *));
    for (int i = 0; i < graphVertix; i++) {
        max_cliques[i] = (int *)malloc(graphVertix * sizeof(int));
    }
    // initialize variables
    int num_max_cliques = 0;
    int max_size = 0;

    //main program
    DFS_findMaxCliques(-1, 0, temp_clique, max_cliques, &num_max_cliques, &max_size, adjMatrix, graphVertix);

    printf("Total Number of Maximum Cliques: %d\n", num_max_cliques);
    for (int i = 0; i < num_max_cliques; i++) {
        printf("Maximum Clique %d: ", i + 1);
        printClique(max_cliques[i], max_size);
        DFS_printMatrixWithClique(adjMatrix, max_cliques[i], max_size, i, graphVertix);
    }
}
