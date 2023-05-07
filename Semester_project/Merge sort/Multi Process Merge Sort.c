#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1;i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            merge_sort(arr, l, m);
            _exit(EXIT_SUCCESS);
        }
        else {
            merge_sort(arr, m + 1, r);
            int status;
            waitpid(pid, &status, 0);
        }
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]){
    int s[] = {2, 3, 4, 56, 0, 32, 44, 5};
    int size = sizeof(s)/sizeof(s[0]);

    clock_t start_time, end_time;
    double total_time;

    start_time = clock(); // start the clock

    merge_sort(s, 0, size-1);

    end_time = clock(); // stop the clock
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    cout<<"sorted array: "<<endl;
    for(int i = 0; i < size; i++)
        cout<<s[i]<<" ";
    cout<<endl;

    cout<<"Time taken: "<<total_time<<" seconds"<<endl;

    return 0;
}

