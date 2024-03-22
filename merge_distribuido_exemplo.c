#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int array[] = {5, 2, 9, 1, 7, 3, 8, 4, 6};  // Array a ser ordenado

    int array_size = sizeof(array) / sizeof(array[0]);
    int local_array[array_size];

    MPI_Scatter(array, array_size, MPI_INT, local_array, array_size, MPI_INT, 0, MPI_COMM_WORLD);

    mergeSort(local_array, 0, array_size - 1);

    MPI_Gather(local_array, array_size, MPI_INT, array, array_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Array ordenado: ");
        for (int i = 0; i < array_size; i++)
            printf("%d ", array[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
