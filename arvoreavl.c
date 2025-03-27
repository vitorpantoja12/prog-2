#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *esq;
    struct No *dir;
    int altura;
}No;

No *raiz = NULL;

int altura(No* no) {
    if (no == NULL) return -1;
    return no->altura;
}

int maior(int a, int b){
    return (a > b) ? a : b;
}

int fator_bl (No *no){
    if (no == NULL)
    {return 0;}
    int alt_esq = -altura(no->esq);
    int alt_dir = altura(no->dir);
    return alt_dir-alt_esq;
}

int verificar (No *no, int num){
    if (no==NULL){
        return 1;
    } else {
        if (no->valor==num)
        {
            return 0;
        }
    }
    verificar (no->esq, num);
    verificar (no->dir, num);
}

No *rot_esq(No *raiz) {
    if (raiz == NULL || raiz->dir == NULL) {
        return raiz;
    }

    No *auxr = raiz->dir;
    No *auxf = auxr->esq;

    auxr->esq = raiz;
    raiz->dir = auxf;

    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));
    auxr->altura = 1 + (altura(auxr->esq) > altura(auxr->dir) ? altura(auxr->esq) : altura(auxr->dir));

    return auxr;
}


No *rot_dir(No *raiz){
    if (raiz == NULL || raiz->dir == NULL) {
        return raiz;
    }
    No *auxr, *auxf;
    auxr = raiz->esq;
    auxf = auxr->dir;
    auxr->dir = raiz;
    raiz->esq = auxf;
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));
    auxr->altura = 1 + (altura(auxr->esq) > altura(auxr->dir) ? altura(auxr->esq) : altura(auxr->dir));
    return auxr;
}

No *rot_diresq (No *raiz){
    raiz->dir = rot_dir(raiz->dir);
    return rot_esq(raiz);
}

No *rot_esqdir (No *raiz){
    raiz->esq = rot_esq(raiz->esq);
    return rot_dir(raiz);
}

No *balanceamento (No *no, int num){
    int fb = fator_bl (no);
    if (no == NULL) return no;
    if (fb>1)
    {
        if (no->esq != NULL && num < no->esq->valor)
        {
            return rot_dir(no);
        } else {
            return rot_diresq(no);}
    } else if (fb<-1)
    {
        if (no->dir != NULL && num > no->dir->valor)
        {
            return rot_esq(no);
        } else {
            return rot_esqdir(no);}
    }
    return no;
}

void inserir (int num){
    if (verificar(raiz, num)){
    No *novo = (No*) malloc(sizeof(No));

    if (novo!=NULL){
        novo-> esq = novo->dir = NULL;
        novo->valor = num;
        novo->altura = 0;

        if (raiz==NULL)
        {
            raiz = novo;
            return;
        } else {
            No *local = raiz;
            No *pai = NULL;

            while (local != NULL)
            {
                pai = local;
                if (local->valor > num)
                {
                    local = local->esq;
                } else {
                    local = local->dir;
                }
            }

            if (num < pai->valor) {
                pai->esq = novo;
            } else {
                pai->dir = novo;
            }
            pai->altura = maior(altura(pai->esq), altura(pai->dir)) + 1;
            raiz = balanceamento(raiz, num);
        }
    }
    else printf ("Erro!");} 
    else {printf ("Valor [%d] já inserido.\n"), num;}}

void imprimir_altura (No *no, int alt, int h){
    if (no == NULL) return;
    
    if (altura(no) == alt)
    {
        printf ("%d ", no->valor);
    }
    imprimir_altura (no->esq, alt, h-1);
    imprimir_altura (no->dir, alt, h-1);
}

void imprimir(No *no){
    int alt = altura(raiz);
    for (int i = 0; i <= alt; i++)
    {
        imprimir_altura (raiz, i, alt);
    }
}

int main (){
    inserir (30);
    inserir (20);
    inserir (50);
    inserir (60);
    inserir (70);
    imprimir(raiz);
}