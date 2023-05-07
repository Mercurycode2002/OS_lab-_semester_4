#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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

struct radix_args {
    int *arr;
    int n;
    int exp;
};

void *multi_thread_radix_sort(void *arg) {
    struct radix_args *args = (struct radix_args *)arg;
    radix_sort(args->arr, args->n, args->exp);
    return NULL;
}

void multi_threading_radix_sort(int arr[], int n) {
    pthread_t threads[n];
    struct radix_args args[n];
    int i, exp = 1;
    int max_num = get_max(arr, n);
    
    while (max_num / exp > 0) {
        for (i = 0; i < n; i++) {
            args[i].arr = arr;
            args[i].n = n;
            args[i].exp = exp;
            pthread_create(&threads[i], NULL, multi_thread_radix_sort, &args[i]);
        }

        for (i = 0; i < n; i++) {
            pthread_join(threads[i], NULL);
        }

        exp *= 10;
    }
}

int main() {
    int arr[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

   

    clock_t start_time = clock();
    multi_threading_radix_sort(arr, n);
    clock_t end_time = clock();

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", total_time);

    return 0;
}

