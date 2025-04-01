#include <stdio.h>

void heap_max (int arr[], int n, int i){
    int esq, dir;
    int maior = i;
    esq = 2*i+1;
    dir = esq + 1;
    if (esq<n && arr[esq]>arr[i]){
        maior = esq;
    }

    if (dir<n && arr[dir]>arr[i])
    {
        maior = dir;
    }

    if (maior != i){
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        heap_max (arr, n, maior);
    }
}

void heapsort (int arr[], int n){
    for (int i = (n / 2) - 1; i >= 0; i--){
        heap_max (arr, n, i);}

    for (int i = n - 1; i > 0; i--)
        {
           int temp = arr[0];
           arr[0] = arr[i];
           arr[i] = temp;
           heap_max (arr, i, 0);
        }
    }

void imprimir(int arr[], int n) {
    for (int i = 0; i < n; ++i){
    printf("[%d] ", arr[i]);
}}

int main (){
    int n;
    printf ("Digite o número de valores na array: \n");
    scanf ("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        printf ("Insira um valor: ");
        scanf ("%d", &array[i]);
    }
    printf ("\n");
    printf ("Array: \n");
    imprimir (array, n);
    printf ("\nArray ordenada: \n");
    heapsort (array, n);
    imprimir (array, n);
}