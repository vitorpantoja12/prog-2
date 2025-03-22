#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    int altura;
    struct No *esq;
    struct No *dir; 
}No;

int maior (int a, int b){
    if (a>b){
        return a;
    } return b;
}

int altura_no (No *no){
    if (no == NULL){
        return -1;
    } else {
        return no->altura;
    }
}

int fatbl (No *no){
    if(no){
        return (altura_no(no->esq) - altura_no(no->dir));}
    else{
        return 0;}
}


void inserir_inicio (int num){
    No *novo = (No*) malloc (sizeof(No));
    if (novo=NULL){
        printf ("Erro!\n");
    } else {
        novo->valor = num;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

No *rot_esq(No *raiz){
    No *auxr, *auxf;
    auxr = raiz->dir;
    auxf = auxr->esq;
    auxr->esq = raiz;
    raiz->dir = auxf;
    raiz->altura = maior(raiz->dir->altura, raiz->esq->altura);
    auxr->altura = maior(raiz->dir->altura, raiz->esq->altura);
}

No *rot_dir(No *raiz){
    No *auxr, *auxf;
    auxr = raiz->esq;
    auxf = auxr->dir;
    auxr->dir = raiz;
    raiz->esq = auxf;
}

No *rot_diresq (No *raiz){
    raiz->dir = rot_dir(raiz->dir);
    return rot_esq(raiz);
}

No *rot_esqdir (No *raiz){
    raiz->esq = rot_esq(raiz->esq);
    return rot_dir(raiz);
}

No *inserir (No *raiz, int num){
    if (raiz==NULL)
    {
        inserir_inicio (num);
    } else {
        if (num<raiz->valor)
        {
            raiz->esq = inserir(raiz->esq, num);
        } else {
            if (num>raiz->valor)
            {
                raiz->esq = inserir(raiz->esq, num);
            } else {
                printf ("Valor já presente na árvore.\n");
            }
        }
        
    }
    
}

No *balancear (No *raiz){
    int fb = fatbl(raiz);
    if (fb < -1 && fatbl(raiz->dir));
    {
        
    }
    
}