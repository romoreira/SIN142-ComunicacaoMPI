#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para intercalar dois sub-arrays
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

int main() {
    // AJUSTE O TAMANHO AQUI
    // Use o mesmo total_n que resultaria no seu teste MPI (ex: n_per_process * world_size)
    int total_n = 200000000; 
    
    int *array = malloc(total_n * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    srand(time(NULL));
    printf("Gerando instância centralizada de %d elementos...\n", total_n);
    for (int i = 0; i < total_n; i++) {
        array[i] = rand() % 100000;
    }

    // Medição de tempo usando clock() (padrão C para sequencial)
    clock_t start_time = clock();

    mergeSort(array, 0, total_n - 1);

    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Ordenação centralizada concluída em: %f segundos\n", time_spent);

    // Validação
    int sorted = 1;
    for(int i=0; i < total_n-1; i++) {
        if(array[i] > array[i+1]) { sorted = 0; break; }
    }
    printf("Array está ordenado corretamente? %s\n", sorted ? "Sim" : "Não");

    free(array);
    return 0;
}
