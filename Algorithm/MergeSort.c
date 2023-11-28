#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int start, int mid, int end);

void mergesort(int arr[], int start, int end){
    if (start < end) {
        int mid = start + (end - start) / 2;

        mergesort(arr, start, mid);
        mergesort(arr, mid+1, end);

        merge(arr, start, mid, end);
    }
}

void merge(int arr[], int start, int mid, int end){
    int len1 = mid-start+1;
    int len2 = end-mid;

    int left[len1], right[len2];

    for (int i = 0; i < len1; i++) {
        left[i] = arr[start+i];
    }

    for (int j = 0; j < len2; j++) {
        right[j] = arr[mid+1+j];
    }

    int i = 0, j = 0, k = start;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
