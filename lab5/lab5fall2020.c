/*
CSE 3318 Prof. Bob Weems Fall 2020 Lab 5 
Samarjit Singh Bons 1001623236
gcc lab5fall2020.c -lm

Kruskal's Euclidian MST using union-find trees
Description: Finding an Euclidean Minimum Spanning Tree using Kruskal's Algorithm
given the number of vertices and the (x,y) coordinates of every vertice.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Declaring variables and structs for vertices and edges
int numVertices,numEdges;
int *parent,*weight,numTrees;

struct edge {
  int tail,head;
  double weight;
};
typedef struct edge edgeType;
edgeType *edgeTab;

struct point {
    int xCo,yCo,position;
};
typedef struct point pointType;
pointType *pointTab;


int find(int x)
// Find root of tree containing x
// Argument: integer x 
{
int i,j,root;

// Find root
for (i=x;
     parent[i]!=i;
     i=parent[i])
  ;
root=i;
// path compression - make all nodes on path
// point directly at the root
for (i=x;
     parent[i]!=i;
     j=parent[i],parent[i]=root,i=j)
  ;
return root;
}

void unionFunc(int i,int j)
// Function to add a subtree to the MST
// Arguments  int i and int j must be roots!
{
if (weight[i]>weight[j])
{
  parent[j]=i;
  weight[i]+=weight[j];
}
else
{
  parent[i]=j;
  weight[j]+=weight[i];
}
numTrees--;
}

int weightAscending(const void* xin, const void* yin)
// Used in call to qsort()
{
edgeType *x,*y;

x=(edgeType*) xin;
y=(edgeType*) yin;
if((x->weight) > (y->weight))
    return 1;
else if((x->weight) < (y->weight))
    return -1;
else 
    return 0;
}

double distance(pointType tail,pointType head)
// Used to find euclidean distance between the head and tail point
// Arguments : pointType tail and pointType head
{
    double sqDistance;
    sqDistance = (head.yCo - tail.yCo)*(head.yCo - tail.yCo) + (head.xCo - tail.xCo)*(head.xCo - tail.xCo);
    sqDistance = sqrt(sqDistance);
    return sqDistance;
}

int main()
{
int i,j,k;
k=0;
int counter = 0;
double MSTweight=0;
int root1,root2;


scanf("%d",&numVertices);
//taking in number of vertices


numEdges=((numVertices*numVertices)-numVertices)/2;

//Dynamic memory allocation
edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
pointTab=(pointType*) malloc(numVertices*sizeof(pointType));
parent=(int*) malloc(numVertices*sizeof(int));
weight=(int*) malloc(numVertices*sizeof(int));

if (!edgeTab || !parent || !weight)
{
  printf("error 2\n");
  exit(0);
}

//Take in the (x,y) coordinates for vertices
for(i=0;i<numVertices;i++)
    scanf("%d %d",&pointTab[i].xCo,&pointTab[i].yCo);


for(i=0;i<numVertices;i++)
    pointTab[i].position = i;

// echo the points
for(i=0;i<numVertices;i++)
    printf("%d %d %d\n",pointTab[i].position,pointTab[i].xCo,pointTab[i].yCo);



// Generate edges and corresponding weights
for(i=0;i<numVertices;i++)
{
    for(j=i+1;j<numVertices;j++){
        edgeTab[k].tail = pointTab[i].position;
        edgeTab[k].head = pointTab[j].position;
        edgeTab[k].weight = distance(pointTab[i],pointTab[j]);
        k++;
    }
}


// Initializing arrays
for (i=0;i<numVertices;i++)
{
  parent[i]=i;
  weight[i]=1;
}

// Each vertices is a tree initially
numTrees=numVertices;

// library sort the edges according to weight
qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);

// for loop to grow the MST 
for (i=0;i<numEdges;i++)
{
  root1=find(edgeTab[i].tail);
  root2=find(edgeTab[i].head);
  if (root1==root2)
    printf("%d %d %lf discarded\n",edgeTab[i].tail,edgeTab[i].head,
      edgeTab[i].weight);
  else
  {
    printf("%d %d %lf included\n",edgeTab[i].tail,edgeTab[i].head,
      edgeTab[i].weight);
    MSTweight+=edgeTab[i].weight;
    unionFunc(root1,root2);
    counter++;
  }
  if(counter==(numVertices-1))
    break;
  //break the for loop when MST reaches every vertice in the graph
}

if (numTrees!=1)
  printf("MST does not exist\n");
printf("Sum of weights of spanning edges %lf\n",MSTweight);
free(edgeTab);
free(parent);
free(weight);
free(pointTab);

}
