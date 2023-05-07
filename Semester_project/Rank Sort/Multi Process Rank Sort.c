#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_N 1000000
#define MAX_NUM 10000
#define PROCESS_MAX 4

int a[MAX_N], sorted[MAX_N];

void rank_sort(int n) {
    int rank[MAX_NUM] = {0};

    for (int i = 0; i < n; ++i) {
        int val = a[i];
        for (int j = 0; j < n; ++j) {
            if (a[j] < val) {
                ++rank[i];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        sorted[rank[i]] = a[i];
    }
}

int main() {
    int s[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int n = sizeof(s) / sizeof(s[0]);

    int process_max = PROCESS_MAX;
    pid_t pid[PROCESS_MAX];
    int pipefd[PROCESS_MAX][2];

    for (int i = 0; i < n; ++i) {
        a[i] = s[i];
    }

    int block_size = n / process_max;
    int start = 0;

    clock_t start_time = clock();

    for (int i = 0; i < process_max; ++i) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid[i] = fork();
        if (pid[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0) { // child process
            close(pipefd[i][0]); // close read end of the pipe
            int end = start + block_size;
            if (i == process_max - 1) {
                end = n;
            }

            for (int j = start; j < end; ++j) {
                write(pipefd[i][1], &a[j], sizeof(int));
            }

            close(pipefd[i][1]); // close write end of the pipe
            exit(EXIT_SUCCESS);
        }
        else { // parent process
            close(pipefd[i][1]); // close write end of the pipe
            start += block_size;
        }
    }

    // wait for child processes to finish
    for (int i = 0; i < process_max; ++i) {
        int status;
        waitpid(pid[i], &status, 0);
    }

    // read the values from the pipes and put them in the a array
    int k = 0;
    for (int i = 0; i < process_max; ++i) {
        int val;
        while (read(pipefd[i][0], &val, sizeof(int)) > 0) {
            a[k++] = val;
        }
        close(pipefd[i][0]);
    }

    rank_sort(n);

    clock_t end_time = clock();

    printf("Sorted array: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
