#include <stdio.h>
#include "SortingAlgorithm.h"

int main(){
    int arr[] = {5,3,2,5,7,8,5,2,5,7,1};
    int size = sizeof(arr) / sizeof(arr[0]);
    //quicksort(arr, 0, size-1);
    bubblesort(arr, size);
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
