#include <stdio.h>

// selectionSort(arr, n);
void selectionSort(int arr[], int n)
{
    int i, j, k;
    // k is the index of minimum number

    for (i = 0; i < n - 1; i++) {
        // Find the minimum element
        k = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[k])
                k = j;

        if(k != j){
            // Swap arr[k] with arr[i]
            int temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
            }
    }
}

// min(arr, n);
int min(int arr[], int n){
    // Find the minimum number
    int min = arr[0];
    for (int i = 0; i < n - 1; i ++){
        if (min > arr[i])
            min = arr[i];
    }
    return min;
}

// max(arr, n);
int max(int arr[], int n){
    // Find the maximum number
    int max = arr[0];
    for (int i = 0; i < n - 1; i ++){
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}
