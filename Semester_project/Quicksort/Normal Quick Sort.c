#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 8

int s[MAX_SIZE] = {2, 3, 4, 56, 0, 32, 44, 5};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

void quicksort(int *arr, int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right);
        quicksort(arr, left, p - 1);
        quicksort(arr, p + 1, right);
    }
}

int main() {
    clock_t start_time, end_time;
    double time_taken;
    start_time = clock();
    
    quicksort(s, 0, MAX_SIZE - 1);
    
    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    printf("Sorted array: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", s[i]);
    }
    printf("\nTime taken: %lf seconds\n", time_taken);
    return 0;
}

