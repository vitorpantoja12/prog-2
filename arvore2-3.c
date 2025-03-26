#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor1, valor2;
    struct No *esq;
    struct No *dir;
    struct No *meio;
    int tipo;
}No;

No *raiz = NULL;

int menor (int valor1, int valor2){
    if (valor1>valor2)
    {
        return valor2;
    } else {
        return valor1;
    }
}

No *inserir_vazio (No *no, int num){
    if (no->valor1==-1)
    {
        no->valor1=num;
    } else {
        if (num < no->valor1)
        {
            int temp = no->valor1;
            no->valor1 = num;
            no->valor2 = temp;
        } else {
            no->valor2 = num;
        }
}}

No *inserir (int num){
    No *novo = (No*) malloc(sizeof(No));
    
}