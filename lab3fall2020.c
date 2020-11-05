// Subset sums by dynamic programming
// CSE 3318 Notes 7

#include <stdio.h>
#include <stdlib.h>

void readInput(int* n,int* m,int** S,int** C)
{
// Loads all input and allocates space
int i;

scanf("%d",n);
scanf("%d",m);

*S=(int*) malloc((*n+1)*sizeof(int));
*C=(int*) malloc((*n+1)*(*m+1)*sizeof(int));
if (!(*S) || !(*C))
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}

(*S)[0]=0;                // Sentinel zero
for (i=1;i<=*n;i++)
  scanf("%d",*S+i);
}

void subsetSum(int n,int m,int* S,int* C)
{
int i,j,potentialSum,card,leftover;

// Initialize table for DP

for(i=0;i<=n;i++){

*(C+(0*(n+1)+i)) = n+1;       //C[0][i]=n+1;
}

for(i=0;i<=m;i++){

*(C+(i*(n+1)+0)) = n+1;       //C[i][0]=n+1;
}  

for(potentialSum=1; potentialSum<=m;potentialSum++){
  for(j=1;j<=n;j++){
    
    leftover = potentialSum-S[j];
    
    if(leftover == 0)
      break;
    
  }
  *(C+(potentialSum*(n+1)+1)) = j;   //C[i][0] = j;
}

// DP base case
// For each potential sum, determine the smallest index such
// that its input value is in a subset to achieve that sum.

for (potentialSum=1; potentialSum<=m; potentialSum ++)
{
  for(card=2;card<=n;card++){

  
    for (j=1;j<=n;j++)
    {
      leftover=potentialSum-S[j];      // To be achieved with other values
      if (leftover>=0 && *(C+(leftover*(n+1))+(card-1)) < j)  //*(C+(leftover*(m+1))+(card-1)) < j              // Indices are included in
        break;                         // ascending order.
    }
    //C[potentialSum][card]=j;
    *(C+(potentialSum*(n+1))+card) = j;
  }
}
}

void writeOutput(int n,int m,int* S,int* C)
{
int i,k,l,j;

// Output the input set
printf("  i   S\n");
printf("-------\n");
for (i=0;i<=n;i++)
  printf("%3d %3d\n",i,S[i]);

// Output the DP table
//if (m<=50)
//{
  printf("   i   card  C\n");
  printf("-----------------\n");
  for (i=0;i<=m;i++){
    for(j=1;j<=n;j++){
    printf("%4d %4d %4d\n",i,j,*(C+(i*(n+1))+j));  
    }
  }
//}

// Output the backtrace

for(k=1;k<=n;k++){
if (*(C+(m*(n+1))+k) == n+1)    
  printf("No solution with %d elements\n",k);
else
{
  printf("Solution with %d elements\n",k);
  printf("  i   S\n");
  printf("-------\n");
  int l = k;
  int s = m;
  
  while(l > 0 && s>0){
    
    printf("%3d %3d\n",*(C+(s*(n+1))+(l)),   S[*(C+(s*(n+1))+(l))]);
                              
    s = s - S[*(C+(s*(n+1))+(l))]; 
    l--;
   // printf("%3d %3d\n",l,s);

  }               //k is current cardinality 
  
  /*for (i=m;i>0;i-=S[*(C+(i*(n+1))+(l))]){                  
    printf("%3d %3d\n",*(C+(i*(n+1))+(l)),S[*(C+(i*(n+1))+(l))]);
    l--;
    
  }*/


}
}




}

int main()
{
int n;    // Size of input set
int m;    // Target value
int *S;   // Input set
int *C;   // Cost table

readInput(&n,&m,&S,&C);
printf("TEST1\n");



subsetSum(n,m,S,C);
printf("TEST2\n");
writeOutput(n,m,S,C);
printf("TEST3\n");
free(S);
free(C);
}

