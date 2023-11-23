#include <stdio.h>
#include <stdbool.h>

void bubblesort(int arr[], int size){
    bool swapped;

    for(int i=0; i<size-1; ++i){
        swapped = false;
        for(int j=0; j<size-1-i; ++j){
            if(arr[j] > arr[j+1]){
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
                swapped = true;
            }
        }
        if(!swapped)break;
    }
}