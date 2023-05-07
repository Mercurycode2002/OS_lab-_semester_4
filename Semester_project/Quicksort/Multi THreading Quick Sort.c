#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define MAX_SIZE 100000
#define MAX_THREADS 4

int array[MAX_SIZE];
int partition(int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;
    return i + 1;
}

typedef struct {
    int left;
    int right;
} thread_data_t;

void *quicksort(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int left = data->left;
    int right = data->right;
    if (left < right) {
        int p = partition(left, right);
        thread_data_t left_data = {left, p - 1};
        thread_data_t right_data = {p + 1, right};
        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, quicksort, &left_data);
        pthread_create(&right_thread, NULL, quicksort, &right_data);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    pthread_exit(NULL);
}

int main() {
    int n = 8;  // size of the array
    int s[] = {2, 3, 4, 56, 0, 32, 44, 5};  // array to be sorted
    for (int i = 0; i < n; i++) {
        array[i] = s[i];
    }
    thread_data_t data = {0, n - 1};

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    pthread_t thread;
    pthread_create(&thread, NULL, quicksort, &data);
    pthread_join(thread, NULL);

    clock_gettime(CLOCK_REALTIME, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Time taken: %f seconds\n", time_taken);
    return 0;
}

