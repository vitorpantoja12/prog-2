#include <stdio.h>

// Função para ajustar um heap máximo a partir de um nó específico
void heapify(int arr[], int n, int i) {
    int largest = i;       // Inicializa o maior como raiz
    int left = 2 * i + 1;  // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        // Troca os elementos
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Chama heapify recursivamente no subárvore afetada
        heapify(arr, n, largest);
    }
}

// Função principal do Heapsort
void heapSort(int arr[], int n) {
    // Constrói um heap máximo (reorganiza o array)
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai elementos um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chama heapify no heap reduzido
        heapify(arr, i, 0);
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Exemplo de uso
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}