#include <stdio.h>

void max_heapify (int array[], int i, int tamanho){
    int esquerdo = 2*i + 1;
    int direito = 2*i + 2;
    int maior;
    if (esquerdo < tamanho && array[esquerdo] > array[i])
    {
        maior = esquerdo;
    } else {
        maior = i;
    }

    if (direito < tamanho && array[direito] > array[maior])
    {
        maior = direito;
    }

    if (maior != i)
    {
        int temp = array[i];
        array[i] = array[maior];
        array[maior] = temp;
        int modificado;
        modificado = maior;
        max_heapify(array, modificado, tamanho);
    }
}

void build_max_heap(int array[], int tamanho) {
    for (int i = (tamanho / 2) - 1; i >= 0; i--) {
        max_heapify(array, i, tamanho);
    }
}

void heapsort(int array[], int tamanho){
    build_max_heap(array, tamanho);
    for (int i = tamanho - 1; i >= 0; i--)
    {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        max_heapify(array, 0, i);
    }
}

void imprimir(int array[], int tamanho){
    printf ("[");
    for (int i = 0; i < tamanho; i++)
    {
        printf (" %d ", array[i]);
    }
    printf ("]\n");
}

int main (){
    int tamanho;

    printf("Insira o número de valores da array: ");
    scanf ("%d", &tamanho);

    int array[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        printf ("Insira o valor %d: ", i+1);
        scanf("%d", &array[i]);
    }

    imprimir(array, tamanho);

    heapsort(array, tamanho);

    imprimir(array, tamanho);
}