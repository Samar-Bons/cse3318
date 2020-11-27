#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int msd(int *A, int lo, int hi, int d, int k){

    printf("Position %d n %d\n",d,(hi-lo));
    
    if(hi==(lo+1)){
        return A[lo];
    }
    int sortSize = hi-lo;

    int *count = (int*)malloc(10*sizeof(int));
    int *slot = (int*)malloc(10*sizeof(int));
    int *temp_slot = (int*)malloc(10*sizeof(int));
    int *temp =  (int*)malloc((sortSize)*sizeof(int));
    int *temp_out =  (int*)malloc((sortSize)*sizeof(int));
    
    for(int i = 0; i < 10; i++)
    {
        count[i] = 0;                                                                  //count[digitAt(A[i],d)]++;
    }

    for(int i = 0; i < sortSize; i++){

        temp[i] = A[lo + i];
    }

    for(int i = 0; i < sortSize; i++){

        count[digitAt(temp[i],d)]++;
    }

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

    

    
    for(int i = 0; i < sortSize; i++){
        *(A + lo + i) = temp_out[i];
    }

    if(d == 1){
        int result = temp_out[k-1];
        //printf("MSD 10 radix: The value with rank %d is %d")
        free(temp);
        free(temp_out);
        free(count);
        free(slot);
        
        return result;
    }



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

    int n,k;

    scanf("%d %d",&n,&k);

    int* A = (int*)malloc(n*sizeof(int));

    for(int j = 0; j < n; j++){
        scanf("%d",&A[j]);
    }

    printf("MSD radix 10 sort: The value with rank %d is %d\n",k,msd(A,0,n,9,k));

    free(A);
    return 0;
}
