#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

int main() {
    int s[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int n = sizeof(s) / sizeof(int);

    clock_t start_time = clock();

    selection_sort(s, n);

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");

    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
