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

void inserir (int num){
    if (verificar(raiz, num)){
    No *novo = (No*) malloc(sizeof(No));

    if (novo!=NULL){
        novo-> esq = novo->dir = NULL;
        novo->valor = num;

        if (raiz==NULL)
        {
            raiz = novo;
            novo->altura = 0;
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
        }
    }
    else printf ("Erro!");} 
    else {printf ("Valor [%d] já inserido.\n"), num;}}

No *rot_esq(No *raiz){
    No *auxr, *auxf;
    auxr = raiz->dir;
    auxf = auxr->esq;
    auxr->esq = raiz;
    raiz->dir = auxf;
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));
    auxr->altura = 1 + (altura(auxr->esq) > altura(auxr->dir) ? altura(auxr->esq) : altura(auxr->dir));
    return auxr;
}

No *rot_dir(No *raiz){
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
    if (fb>1)
    {
        if (num < no->esq->valor)
        {
            return rot_dir(no);
        } else {
            no->esq = rot_esq(no->esq);
            return rot_esqdir(no);}
    } else if (fb<-1)
    {
        if (num > no->dir->valor)
        {
            return rot_esq(no);
        } else {
            no->dir = rot_dir(no->dir);
            return rot_diresq(no);}
    }
    return no;
}

void imprimir(No *no) {
    if (no==NULL) return;
        if (no==raiz)
        {
            printf ("     ");
        }
        printf (" [%d] ", no->valor);
        if (no->esq!=NULL)
        {
            printf ("\n   / \n");
        }
        imprimir (no->esq);
        if (no->dir!=NULL)
        {
            printf ("\n          \\\n");
        }
        imprimir (no->dir);

}

int main (){
    inserir (30);
    inserir (50);
    inserir (60);
    imprimir(raiz);
}