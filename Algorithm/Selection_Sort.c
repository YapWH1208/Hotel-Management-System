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
