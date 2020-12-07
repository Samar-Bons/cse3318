//CSE 3318 Prof. Bob Weems Fall 2020 Lab 4
//Samarjit Singh Bons 1001623236
// gcc -o lab4fall2020 lab4fall2020.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
Function: digitAt(int num, int d);
Parameters: integer num; integer d
The function returns the value at the digit's place 'd' in the the integer num.
*/
int digitAt(int num, int d)
{
    if(d > 9 || d < 1){
        return -1;
    }
    if(d == 1){
        return num%10;
    }
       
    for(int i = d; i>1; i--){
        num = num/10;
    }
    
    num = num%10;

    return num;

}


/*
Function: int msd(int *A, int lo, int hi, int d, int k);
Parameters: int array A; integers lo,hi,d,k
Function performs a counting sort according to the value at digit 'd' in the array A
from lo to hi subscript. The function is used recursively to perform a most siginificant digit 
Radix sort to find the kth smallest number in the array A.
*/
int msd(int *A, int lo, int hi, int d, int k){

    printf("Position %d n %d\n",d,(hi-lo));
    
    if(hi==(lo+1)){
        return A[lo];
    }
    int sortSize = hi-lo;
    
    //dynamic allocation for helper arrays
    int *count = (int*)malloc(10*sizeof(int));
    int *slot = (int*)malloc(10*sizeof(int));
    int *temp_slot = (int*)malloc(10*sizeof(int));
    int *temp =  (int*)malloc((sortSize)*sizeof(int));
    int *temp_out =  (int*)malloc((sortSize)*sizeof(int));
    
    //setting the count table to 0's
    for(int i = 0; i < 10; i++)
    {
        count[i] = 0;                                                                  
    }

    //copy the required part to be sorted to the temp array
    for(int i = 0; i < sortSize; i++){

        temp[i] = A[lo + i];
    }

    //increment the count table
    for(int i = 0; i < sortSize; i++){

        count[digitAt(temp[i],d)]++;
    }

    //make the slot table
    slot[0] = 0;
    for(int i = 1; i < 10; i++){
        slot[i] = slot[i-1] + count[i-1];
    }
    
    for(int i = 0 ; i < 10; i++){
        temp_slot[i] = slot[i];
    }
    
    for(int i = 0; i < sortSize; i++){
        temp_out[temp_slot[digitAt(temp[i],d)]++] = temp[i];
    }
    free(temp_slot);

    

    //copy the sorted elements back to array A
    for(int i = 0; i < sortSize; i++){
        *(A + lo + i) = temp_out[i];
    }

    //return the kth smallest element of temp_out if d == 1
    if(d == 1){
        int result = temp_out[k-1];
        free(temp);
        free(temp_out);
        free(count);
        free(slot);
        
        return result;
    }


    //recursively call msd on the new lo/hi range on A, with keys as values at digit 'd-1'
    for(int i = 1; i < 10; i++){
        if((k-1)<slot[i]){
            int low = lo;
            lo = low + slot[i-1];
            hi = low + slot[i];
            k = k - slot[i-1];
            free(temp);
            free(temp_out);
            free(count);
            free(slot);
            return msd(A,lo,hi,d-1,k);
        }
    }
    
    //if (k-1) is bigger than any slot values but smaller than (slot[9]+count[9])
    if((k-1)<(slot[9]+count[9])){

        int low = lo;
        lo = low + slot[9];
        hi = low + (slot[9]+count[9]);
        k = k - slot[9];
        free(temp);
        free(temp_out);
        free(count);
        free(slot);
        return msd(A,lo,hi,d-1,k);
    }
}

int main(){

    //accept n and k values from user, dynamically allocate array A and accept its values
    int n,k;
    scanf("%d %d",&n,&k);
    int* A = (int*)malloc(n*sizeof(int));
    for(int j = 0; j < n; j++){
        scanf("%d",&A[j]);
    }

    //call msd function to find kth smallest number in A
    printf("MSD radix 10 sort: The value with rank %d is %d\n",k,msd(A,0,n,9,k));

    free(A);
    return 0;
}
