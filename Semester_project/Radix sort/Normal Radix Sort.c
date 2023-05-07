#include <stdio.h>
#include <time.h>

int get_max(int a[], int n) {
    int i;
    int max = a[0];
    for (i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

void radix_sort(int a[], int n) {
    int bucket[10][10], bucket_cnt[10];
    int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
    lar = get_max(a, n);
    while (lar > 0) {
        NOP++; // No of passes
        lar /= 10; // largest number
    }
    for (pass = 0; pass < NOP; pass++) {
        for (i = 0; i < 10; i++) {
            bucket_cnt[i] = 0;
        }
        for (i = 0; i < n; i++) {
            r = (a[i] / divisor) % 10;
            bucket[r][bucket_cnt[r]] = a[i];
            bucket_cnt[r] += 1;
        }
        i = 0;
        for (k = 0; k < 10; k++) {
            for (j = 0; j < bucket_cnt[k]; j++) {
                a[i] = bucket[k][j];
                i++;
            }
        }
        divisor *= 10;
        printf("After pass %d : ", pass + 1);
        for (i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
}

int main() {
    int i, n;
    int a[8] = {2, 3, 4, 56, 0, 32, 44, 5};
    n = sizeof(a) / sizeof(int);
    printf("The size of array is: %d\n", n);

    clock_t start_time = clock();
    radix_sort(a, n);
    clock_t end_time = clock();

    printf("Sorted items: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken to sort the array: %lf seconds\n", time_taken);

    return 0;
}

