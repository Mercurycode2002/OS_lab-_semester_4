#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void radix_sort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++) {
        count[ (arr[i]/exp)%10 ]++;
    }

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void multi_process_radix_sort(int arr[], int n) {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid < 0) {
        printf("Error in creating fork!");
        exit(1);
    }
    else if (pid == 0) {
        close(fd[0]);
        int exp = 1;
        int max_num = get_max(arr, n);
        while (max_num / exp > 0) {
            radix_sort(arr, n, exp);
            exp *= 10;
        }
        write(fd[1], arr, n*sizeof(int));
        close(fd[1]);
        exit(0);
    }
    else {
        close(fd[1]);
        wait(NULL);
        int sorted_arr[n];
        read(fd[0], sorted_arr, n*sizeof(int));
        close(fd[0]);
        for (int i = 0; i < n; i++) {
            arr[i] = sorted_arr[i];
        }
    }
}

int main() {
    int arr[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    clock_t t1, t2;
    t1 = clock();
    multi_process_radix_sort(arr, n);
    t2 = clock();
    double time_taken = ((double)t2 - t1) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time taken by radix sort: %f seconds\n", time_taken);

    return 0;
}

