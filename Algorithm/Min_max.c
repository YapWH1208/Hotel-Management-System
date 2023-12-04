void maxmin(int arr[], int i, int j, int *max, int *min) {
    // Find the minimum and maximum number
    // If the array has only one elements
    if (i == j) {
        *max = arr[i];
        *min = arr[i];
    }
    // If the array has two elements
    else if (i == j - 1) {
        if (arr[i] < arr[j]) {
            *max = arr[j];
            *min = arr[i];
        }
        else {
            *max = arr[i];
            *min = arr[j];
        }
    }
    // If the array has more than two elements
    else {
        int mid = (i + j) / 2;
        int max1, min1;
        maxmin(arr, i, mid, max, min);
        maxmin(arr, mid + 1, j, &max1, &min1);

        if (*max < max1) {
            *max = max1;
        }
        if (*min > min1) {
            *min = min1;
        }
    }
}

//int main() {
//    int arr[] = { 3, 6, 1, 11, 4, 10 };
//    int n = sizeof(arr) / sizeof(arr[0]);
//    int max = arr[0];
//    int min = arr[0];
//
//    maxmin(arr, 0, n - 1, &max, &min);
//
//    printf("Maximum element: %d\n", max);
//    printf("Minimum element: %d\n", min);
//
//    return 0;
//}
