#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 8
#define NUM_THREADS 4

int arr[ARRAY_SIZE];

void *selection_sort(void *arg) {
    int start = *(int *)arg;
    int end = start + (ARRAY_SIZE / NUM_THREADS);

    for (int i = start; i < end - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < end; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Initialize the array with random numbers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
    }

    // Print the unsorted array
    printf("Unsorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Create threads for sorting
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i * (ARRAY_SIZE / NUM_THREADS);
        pthread_create(&threads[i], NULL, selection_sort, &thread_args[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge the sorted subarrays
    for (int i = 0; i < ARRAY_SIZE; i += (ARRAY_SIZE / NUM_THREADS)) {
        int start = i;
        int end = i + (ARRAY_SIZE / NUM_THREADS);
        for (int j = start; j < end; j++) {
            int min_index = j;
            for (int k = j + 1; k < end; k++) {
                if (arr[k] < arr[min_index]) {
                    min_index = k;
                }
            }
            int temp = arr[j];
            arr[j] = arr[min_index];
            arr[min_index] = temp;
        }
    }

    // Print the sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
