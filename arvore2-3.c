#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor1, valor2, valortemp;
    struct No *esq;
    struct No *dir;
    struct No *meio;
    int tipo;
}No;

No *raiz = NULL;

int meio (int valor1, int valor2, int valor3){
    if ((valor3<valor1))
    {
        return 1;
    } else {
        if (valor3>valor2)
        {
            return 2;
        } else {
        return 3;}
    }
}

No *ordenar (No *no){
    if (no->valor1>no->valor2){
        int temp = no->valor2;
        no->valor2 = no->valor1;
        no->valor1 = temp;
        return no;
    } else return no;
}

No *inserir_cheio (No *no, int num){
    int poss = meio(no->valor1, no->valor2, no->valortemp);
    switch(poss) {
        case 1:
        no->esq->valor1 = no->valortemp;
        no->dir->valor1 = no->valor2;
        return no;

        case 2:
        no->esq->valor1 = no->valor1;
        no->valor1 = no->valor2;
        no->dir->valor1 = no->valortemp;
        return no;

        case 3:
        no->esq->valor1 = no->valor1;
        no->valor1 = no->valortemp;
        no->dir->valor1 = no->valor2;
        return no;

        default:
        return no;
    }
}

No *inserir_valor (No *no, int num){
        switch(no->tipo) {
            case 1:
            no->valor2 = num;
            no = ordenar(no);
            no->tipo = 2;
            return no;

            case 2:
            no->valortemp = num;
            no = inserir_cheio(no, num);
            return no;

            default:
            no->valor1 = num;
            no->tipo = 1;
            no->esq = no->dir = no->meio = NULL;
            return no;
        }
    }

No *comp (No *no, int num){
    if (no->tipo==1)
    {
    if (num>no->valor1)
    {
        return inserir_valor(no->esq, num);
    } else {
        return inserir_valor(no->dir, num);
    }} else {
        int poss = meio(no->valor1, no->valor2, no->valortemp);
        switch(poss) {
            case 1:
            return no->esq;
    
            case 2:
            return no->dir;
    
            case 3:
            return no->meio;
    
            default:
            return no;
        };
    }
}

No *inserir_no (int num){
    No *pos;
    if (raiz == NULL ||(raiz->esq == NULL && raiz->dir == NULL))
    {
        raiz = inserir_valor(raiz, num);
    } else {
        pos = comp(raiz, num);
        if (pos->tipo==1){
            inserir_valor(pos, num);
        } else {
            inserir_cheio(pos, num);
        }
    }
}