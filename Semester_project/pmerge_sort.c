#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void merge(int arr[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1], right[n2];
    for (int i = 0; i < n1; i++) {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        int pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // child process
            merge_sort(arr, start, mid);
            exit(0);
        } else {
            // parent process
            merge_sort(arr, mid + 1, end);
            wait(NULL);
            merge(arr, start, mid, end);
        }
    }
}

int main() {
    int arr[] = {5, 1, 8, 4, 2, 9, 3, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
