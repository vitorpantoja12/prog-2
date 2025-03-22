#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    No *esq;
    No *dir;
}No;

No *raiz = NULL;

void inserir (int num){
    No *novo = (No*) malloc(sizeof(No));

    if (novo==NULL){
        printf ("Erro!");
    } else {
        if (raiz==NULL)
        {
            novo->valor=num;
            raiz = novo;
        } else {
            No *temp = raiz;
            while (temp!=NULL){
            if (temp->valor < num)
            {
                temp = temp->esq;
            } else {
                if (temp->valor < num){
                    temp = temp->dir;}
                }
            }
            
        }
    }
}