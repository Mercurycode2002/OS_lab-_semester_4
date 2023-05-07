#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_N 1000000
#define MAX_NUM 10000
#define THREAD_MAX 4

int s[] = {2, 3, 4, 56, 0, 32, 44, 5};
int sorted[MAX_N];
int n = 8;

void *rank_sort(void *arg) {
    int id = *(int*) arg;
    int block_size = n / THREAD_MAX;
    int start = id * block_size;
    int end = start + block_size;
    if (id == THREAD_MAX - 1) {
        end = n;
    }

    int rank[MAX_NUM] = {0};
    for (int i = start; i < end; ++i) {
        int val = s[i];
        for (int j = 0; j < n; ++j) {
            if (s[j] < val) {
                ++rank[i];
            }
        }
    }

    for (int i = start; i < end; ++i) {
        sorted[rank[i]] = s[i];
    }

    pthread_exit(NULL);
}

int main() {
    clock_t start_time, end_time;
    double total_time;

    start_time = clock();

    pthread_t threads[THREAD_MAX];
    int thread_ids[THREAD_MAX];
    for (int i = 0; i < THREAD_MAX; ++i) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, rank_sort, &thread_ids[i])) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < THREAD_MAX; ++i) {
        if (pthread_join(threads[i], NULL)) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    end_time = clock();

    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    printf("Time taken: %f seconds\n", total_time);

    return 0;
}

