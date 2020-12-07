// Kruskal's MST using union-find trees

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
// i and j must be roots!
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
{
    double sqDistance;
    sqDistance = (head.yCo - tail.yCo)*(head.yCo - tail.yCo) + (head.xCo - tail.xCo)*(head.xCo - tail.xCo);
    sqDistance = sqrt(sqDistance);
    return sqDistance;
}

int main()
{
int i,j,k;
int counter = 0;
double MSTweight=0;
int root1,root2;

scanf("%d",&numVertices);
numEdges=((numVertices*numVertices)-numVertices)/2; 
edgeTab=(edgeType*) malloc(numEdges*sizeof(edgeType));
pointTab=(pointType*) malloc(numVertices*sizeof(pointType));
parent=(int*) malloc(numVertices*sizeof(int));
weight=(int*) malloc(numVertices*sizeof(int));
if (!edgeTab || !parent || !weight)
{
  printf("error 2\n");
  exit(0);
}
for(i=0;i<numVertices;i++)
    scanf("%d %d",&pointTab[i].xCo,&pointTab[i].yCo);
    //pointTab[i].position = i;

//printf("\ntest");


for(i=0;i<numVertices;i++)
    pointTab[i].position = i;

for(i=0;i<numVertices;i++)
    printf("%d %d %d\n",pointTab[i].position,pointTab[i].xCo,pointTab[i].yCo);


k=0;

for(i=0;i<numVertices;i++)
{
    for(j=i+1;j<numVertices;j++){
        edgeTab[k].tail = pointTab[i].position;
        edgeTab[k].head = pointTab[j].position;
        edgeTab[k].weight = distance(pointTab[i],pointTab[j]);
        k++;
    }
}

//for (i=0;i<numEdges;i++)
  //scanf("%d %d %d",&edgeTab[i].tail,&edgeTab[i].head,&edgeTab[i].weight);

for (i=0;i<numVertices;i++)
{
  parent[i]=i;
  weight[i]=1;
}
numTrees=numVertices;
qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);
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
}
if (numTrees!=1)
  printf("MST does not exist\n");
printf("Sum of weights of spanning edges %lf\n",MSTweight);
free(edgeTab);
free(parent);
free(weight);
free(pointTab);

}
