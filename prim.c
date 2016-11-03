#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define buffer_size 500
#define MAX_EDGE_WEIGHT 100
#define INFINITE 999

//function to print a matrix.
void print_matrix(int **graph, int n)
{
    int i,j;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Function to allocate memory to matrix.
int** memory_allocate(int size){
    int **matrix, i;
    matrix = (int **)calloc(size, sizeof(int *));
    if(matrix == NULL){
        printf("Error in memory allocation \n");
        exit(0);
    }
    for(i = 0; i < size; i++){
        matrix[i] = (int *)calloc(size, sizeof(int));
        if(matrix[i] == NULL)
        {
            printf("Error in memory allocation \n");
            exit(0);
        }
    }
    return matrix;
}

int main(int argc,char* argv[])
{
    /* argc should be 2 for correct execution */
    if(argc != 2)
    {
        /* We print argv[0] assuming it is the program name */
        printf("usage: %s filename",argv[0]);
    }else{
        // Assume argv[1] is a filename to open
        FILE *file = fopen(argv[1],"r");
        /* fopen returns 0, the NULL pointer, on failure */
        if (!file){
            printf("Couldn't open %s for reading\n",argv[1]);
            return 0;
        }else{
            printf("\nImplementation of Prim's algorithm\n");
            int minimum,minimumcost=0;
            int visited[10]={0};
//            int a,b,u,v;
            int matrix_index_a, matrix_index_b;
            int visited_index_u, visited_index_v;
            int new_edge=1;
            int** adjacency_matrix = memory_allocate(MAX_EDGE_WEIGHT + 1);
            int total_vertices;total_vertices=0;
            char line_buffer[buffer_size];
            int matrix_size;matrix_size=0;
            char* filedata=(char*)malloc(sizeof(char));
            int i=1,j=1;
            // Code to read data from file and store in an array
            while(fgets(line_buffer,buffer_size,file)!=NULL){
                filedata=strtok(line_buffer,",");
                while(filedata!=NULL){
                    adjacency_matrix[i][j] = atoi(filedata);
                    j++;
                    filedata=strtok(NULL,",");
                }
                i++; j=1;
                matrix_size++;
            }
            fclose(file);
            printf("\nTotal number of vertices : %d",matrix_size);
            printf("\n\nAdjacency matrix: \n");
            print_matrix(adjacency_matrix,matrix_size);
            
            // Code to initialize the matrix
            for(i=1;i<=matrix_size;i++)
                for(j=1;j<=matrix_size;j++)
                {
                    if(adjacency_matrix[i][j]==0)
                        adjacency_matrix[i][j]=INFINITE;
                }
            
            visited[1]=1;
            printf("\nThe edges of Minimum Cost Spanning Tree are\n");
            while(new_edge < matrix_size){
                for(i=1,minimum=INFINITE;i<=matrix_size;i++)
                    for(j=1;j<=matrix_size;j++)
                        if(adjacency_matrix[i][j]< minimum)
                            if(visited[i]!=0){
                                minimum=adjacency_matrix[i][j];
                                matrix_index_a = visited_index_u =i;
                                matrix_index_b = visited_index_v =j;
                            }

                if(visited[visited_index_u]==0 || visited[visited_index_v]==0){
                    printf("Edge %d:\t(%d %d)\tcost:\t%d\n",new_edge++,matrix_index_a,matrix_index_b,minimum);
                    minimumcost+=minimum;
                    visited[matrix_index_b]=1;
                }
                
                adjacency_matrix[matrix_index_a][matrix_index_b] = adjacency_matrix[matrix_index_b][matrix_index_a]=INFINITE;
                
            }
             printf("\nMinimun cost : %d\n",minimumcost);
        }
}
}