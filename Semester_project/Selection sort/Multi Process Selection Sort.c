#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 8

void selection_sort(int arr[], int start, int end) {
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
}

int main() {
    int arr[SIZE] = {2, 3, 4, 56, 0, 32, 44, 5};
    
    int mid = SIZE / 2;

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time); // Start timer

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        selection_sort(arr, 0, mid);
       
        exit(0);
    } else if (pid > 0) {
        // Parent process
        selection_sort(arr, mid, SIZE);
       

        // Wait for child process to complete
        wait(NULL);

        // Merge two sorted halves
        int merged_arr[SIZE];
        int i = 0, j = mid, k = 0;
        while (i < mid && j < SIZE) {
            if (arr[i] < arr[j]) {
                merged_arr[k++] = arr[i++];
            } else {
                merged_arr[k++] = arr[j++];
            }
        }
        while (i < mid) {
            merged_arr[k++] = arr[i++];
        }
        while (j < SIZE) {
            merged_arr[k++] = arr[j++];
        }

        // Print sorted array
        printf("Sorted array:\n");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", merged_arr[i]);
        }
        printf("\n");

        clock_gettime(CLOCK_MONOTONIC, &end_time); // End timer

        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
        printf("Elapsed time: %f seconds\n", elapsed_time);
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}

