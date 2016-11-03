#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define buffer_size 500
#define INFINITY 999
#define MAX_EDGE_WEIGHT 100

//structure to represent a weighted edge in graph
struct Edge
{
int source;
int destination;
int weight;
};

//Structure array
struct Edge edges[buffer_size];
int total_edges;

int random_number_generator(int lower_limit,int higher_limit){
   int random_number;
   random_number = lower_limit+rand()%(higher_limit-lower_limit+1);
   return random_number;
}

//function to perform the union of two sets x and y.
int union3(int repx,int repy,int* set,int* height)
{
    int value;
    if(height[repx]==height[repy])
    {
        height[repx]++;
        //y tree point to x tree
        set[repy]=repx;
        value = set[repy];
    }else{
        if(height[repx]>height[repy]){
            //y tree point to x tree
            set[repy]=repx;
            value = set[repy];
        }else{
            //x tree point to y tree
            set[repx]=repy;
            value = set[repx];
        }
    }
    return value;
}

//function to find set of an element.
int find3(int x,int* set)
{
    int root=x;
    while(root!=set[root])
        root=set[root];
    
    while(x!=root)
    {
        int parent=set[x];
        set[x]=root;
        x=parent;
    }
    return root;
}

//Code for the randomized quick sort
void quick_sort(struct Edge input_edge_array[],int lower_limit,int higher_limit)
{
int randomIndex,i,j;
struct Edge temp;
struct Edge pivot_element;

if(lower_limit<higher_limit){
    srand(time(NULL));
    randomIndex = random_number_generator(lower_limit,higher_limit);
    temp=input_edge_array[higher_limit];
    input_edge_array[higher_limit]=input_edge_array[randomIndex];
    input_edge_array[randomIndex]=temp;
    pivot_element=input_edge_array[higher_limit];
    i=lower_limit;
    for(j=lower_limit;j<higher_limit;j++){
        if(input_edge_array[j].weight<=pivot_element.weight){
            temp=input_edge_array[j];
            input_edge_array[j]=input_edge_array[i];
            input_edge_array[i]=temp;
            i++;
        }
    }
    input_edge_array[higher_limit]=input_edge_array[i];
    input_edge_array[i]=pivot_element;
    quick_sort(input_edge_array,lower_limit,i-1);
    quick_sort(input_edge_array,i+1,higher_limit);
}
}

//COde to print the edeges of tree
void printMinCostSpanTree(struct Edge result[],int size){
    int i,j;j=0;
    int minimumcost;minimumcost=0;
    printf("\nThe edges of Minimum Cost Spanning Tree are\n");
    for(i=0;i<size;i++)
    {
        j=i;j++;
        minimumcost = minimumcost + result[i].weight;
        printf("Edge %d:\t(%d,%d) cost : %d\n",j,result[i].source,result[i].destination,result[i].weight);
    }
    printf("\nMinimun cost : %d\n",minimumcost);
    printf("\n");
}

void kruskal_algo(int total_vertices,int** graph_matrix)
{
int i,k;k=0;
int edge_src, edge_dest;
int height[total_vertices];
int set[total_vertices];
struct Edge result[total_vertices-1];
int ucomp,vcomp;

for(i=0;i<total_vertices;i++){
    set[i]=i;
    height[i]=1;
}

for(i=0;i<total_edges;i++)
{
    edge_src = edges[i].source;
    edge_dest = edges[i].destination;
    ucomp=find3(edge_src,set);
    vcomp=find3(edge_dest,set);
    
    if(ucomp!=vcomp)
    {
        result[k].source=edges[i].source+1;
        result[k].destination=edges[i].destination+1;
        result[k].weight=edges[i].weight;
        k++;
        union3(ucomp,vcomp,set,height);
    }
}

printMinCostSpanTree(result,k);

}

//Function to de-allocate memory allocated to matrix.
void free_allocated_memory(int **array, int size){
int i;
for(i = 0; i < size; i++){
    free(array[i]);
}
free(array);
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

//function to print a matrix.
void print_matrix(int **graph, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
        printf("\nImplementation of Kruskal's algorithm\n");
        int** adjacency_matrix = memory_allocate(MAX_EDGE_WEIGHT + 1);;
        int total_vertices;total_vertices=0;
        char line_buffer[buffer_size];
        int matrix_size;matrix_size=0;
        char* filedata=(char*)malloc(sizeof(char));
        int i=0,j=0;
//        Code to read data from file and store in an array
        while(fgets(line_buffer,buffer_size,file)!=NULL){
            filedata=strtok(line_buffer,",");
            while(filedata!=NULL){
                adjacency_matrix[i][j] = atoi(filedata);
                j++;
                filedata=strtok(NULL,",");
            }
            i++; j=0;
            matrix_size++;
        }
        fclose(file);
        total_vertices = matrix_size;
                if(total_vertices>0){
                    
                    int i,j,k=0;
                    char node[total_vertices][total_vertices];
                    for(i=0;i<total_vertices;i++){
                        for(j=i+1;j<total_vertices;j++){
                            if(adjacency_matrix[i][j]!=0 && adjacency_matrix[i][j] != INFINITY){
                                node[i][j]=1;
                                node[j][i]=1;
                            }else{
                                node[i][j]=0;
                                node[j][i]=0;
                            }
                        }
                    }
                    
                    for(i=0;i<total_vertices;i++){
                        for(j=0;j<total_vertices;j++){
                            if(node[i][j]==1){
                                edges[k].source=i;
                                edges[k].destination=j;
                                edges[k].weight=adjacency_matrix[i][j];
                                k++;
                                node[j][i]=0;
                            }
                        }
                    }
                    total_edges=k;
                    quick_sort(edges,0,total_edges-1);
                    printf("\nTotal number of vertices : %d",matrix_size);
                    printf("\n\nAdjacency matrix:\n");
                    print_matrix(adjacency_matrix,total_vertices);
                    kruskal_algo(total_vertices,adjacency_matrix);
                }
            free_allocated_memory(adjacency_matrix,total_vertices);
        
    }
}
return 1;
}
