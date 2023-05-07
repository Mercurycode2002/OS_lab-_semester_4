#include <stdio.h>
#include <time.h>

void rank_sort(int a[], int n) {
    int rank[n], sorted[n];
    
    for (int i = 0; i < n; i++) {
        rank[i] = 1;
        for (int j = 0; j < n; j++) {
            if (a[j] < a[i]) {
                rank[i]++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        sorted[rank[i]-1] = a[i];
    }
    
    for (int i = 0; i < n; i++) {
        a[i] = sorted[i];
    }
}

int main() {
    int a[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int n = sizeof(a) / sizeof(a[0]);
    
    
    
    clock_t start = clock();
    
    rank_sort(a, n);
    
    clock_t end = clock();
    
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    
    printf("\nTime taken: %f seconds\n", time_taken);
    
    return 0;
}

