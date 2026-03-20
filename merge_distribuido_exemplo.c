#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int array[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = array[left + i];
    for (j = 0; j < n2; j++) R[j] = array[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { array[k] = L[i]; i++; }
        else { array[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { array[k] = L[i]; i++; k++; }
    while (j < n2) { array[k] = R[j]; j++; k++; }

    free(L);
    free(R);
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
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n_per_process = 100000000; 
    int total_n = n_per_process * world_size;
    
    int *full_array = NULL;
    int *local_array = malloc(n_per_process * sizeof(int));

    if (world_rank == 0) {
        full_array = malloc(total_n * sizeof(int));
        srand(time(NULL));
        printf("Gerando instância de %d elementos...\n", total_n);
        for (int i = 0; i < total_n; i++) {
            full_array[i] = rand() % 100000; 
        }
    }

    double start_time = MPI_Wtime();

    MPI_Scatter(full_array, n_per_process, MPI_INT, local_array, 
                n_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo ordena sua fatia local
    mergeSort(local_array, 0, n_per_process - 1);

    MPI_Gather(local_array, n_per_process, MPI_INT, full_array, 
               n_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        // Em vez de mergeSort total, fazemos apenas o merge das partes já ordenadas
        // Se world_size for 2, fazemos 1 merge. 
        // Se for mais, precisaríamos de um loop de merges, mas para 2 processos:
        if (world_size == 2) {
            merge(full_array, 0, n_per_process - 1, total_n - 1);
        } else {
            // Caso genérico para mais processos (simplificado para fins didáticos)
            mergeSort(full_array, 0, total_n - 1);
        }

        double end_time = MPI_Wtime();
        printf("Tempo MPI Otimizado: %f segundos\n", end_time - start_time);
        
        // Validação
        int sorted = 1;
        for(int i=0; i < total_n-1; i++) {
            if(full_array[i] > full_array[i+1]) { sorted = 0; break; }
        }
        printf("Ordenado corretamente? %s\n", sorted ? "Sim" : "Não");
        
        free(full_array);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}
