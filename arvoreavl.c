#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
    int altura;
} No;

No *raiz = NULL;

// Função para calcular a altura do nó
int altura(No* no) {
    if (no == NULL) return -1;
    return no->altura;
}

// Função para calcular o fator de balanceamento
int fator_bl(No *no) {
    if (no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

// Rotação à esquerda
No *rot_esq(No *raiz) {
    No *auxr = raiz->dir;
    No *auxf = auxr->esq;

    auxr->esq = raiz;
    raiz->dir = auxf;

    // Atualiza as alturas
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));
    auxr->altura = 1 + (altura(auxr->esq) > altura(auxr->dir) ? altura(auxr->esq) : altura(auxr->dir));

    return auxr; // Nova raiz da subárvore
}

// Rotação à direita
No *rot_dir(No *raiz) {
    No *auxr = raiz->esq;
    No *auxf = auxr->dir;

    auxr->dir = raiz;
    raiz->esq = auxf;

    // Atualiza as alturas
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));
    auxr->altura = 1 + (altura(auxr->esq) > altura(auxr->dir) ? altura(auxr->esq) : altura(auxr->dir));

    return auxr; // Nova raiz da subárvore
}

// Rotação dupla direita-esquerda
No *rot_diresq(No *raiz) {
    raiz->dir = rot_dir(raiz->dir);
    return rot_esq(raiz);
}

// Rotação dupla esquerda-direita
No *rot_esqdir(No *raiz) {
    raiz->esq = rot_esq(raiz->esq);
    return rot_dir(raiz);
}

// Função para balancear um nó
No *balanceamento(No *no) {
    if (no == NULL) return no;

    int fb = fator_bl(no);

    // Desbalanceamento para a esquerda
    if (fb > 1) {
        if (fator_bl(no->esq) < 0) {
            no->esq = rot_esq(no->esq);
        }
        return rot_dir(no);
    }

    // Desbalanceamento para a direita
    if (fb < -1) {
        if (fator_bl(no->dir) > 0) {
            no->dir = rot_dir(no->dir);
        }
        return rot_esq(no);
    }

    return no; // Nenhuma rotação necessária
}

// Função para inserir um novo valor na árvore AVL
No *inserir(No *no, int num) {
    if (no == NULL) {
        No *novo = (No*) malloc(sizeof(No));
        if (novo == NULL) {
            printf("Erro ao alocar memória!\n");
            return NULL;
        }
        novo->valor = num;
        novo->esq = novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }

    // Inserção recursiva
    if (num < no->valor) {
        no->esq = inserir(no->esq, num);
    } else if (num > no->valor) {
        no->dir = inserir(no->dir, num);
    } else {
        return no; // Valor duplicado não permitido
    }

    // Atualiza a altura
    no->altura = 1 + (altura(no->esq) > altura(no->dir) ? altura(no->esq) : altura(no->dir));

    // Balanceia a árvore
    return balanceamento(no);
}

// Função para imprimir a árvore em pré-ordem (para testes)
void imprimir(No *no) {
    if (no == NULL) return;
    printf("[%d] ", no->valor);
    imprimir(no->esq);
    imprimir(no->dir);
}

// Função principal
int main() {
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 30);

    printf("Árvore AVL (pré-ordem): ");
    imprimir(raiz);
    printf("\nAltura da raiz: %d\n", altura(raiz));

    return 0;
}
