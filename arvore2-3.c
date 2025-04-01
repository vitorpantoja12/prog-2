#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor1, valor2, valortemp;
    struct No *esq, *dir, *meio, *pai;
    int tipo;
} No;

No *raiz = NULL;

// Função para criar um nó
No *criar_no(int num, No *pai) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->valor1 = num;
    novo->valor2 = 0;
    novo->tipo = 1;
    novo->esq = novo->dir = novo->meio = NULL;
    novo->pai = pai;
    return novo;
}

// Função para ordenar os valores dentro do nó
void ordenar(No *no) {
    if (no->valor1 > no->valor2) {
        int temp = no->valor1;
        no->valor1 = no->valor2;
        no->valor2 = temp;
    }
}

// Split para filho esquerdo
void split_filhoesq(No *no) {
    No *novo = criar_no(no->valor2, no->pai);
    
    // O valor do meio sobe para o pai
    no->pai->valor2 = no->valor1;
    
    // Ajustando os filhos do pai
    no->pai->meio = novo;
    no->valor2 = 0;
    no->tipo = 1;
    
    // Ajustando ponteiros
    novo->pai = no->pai;
}

// Split para filho direito
void split_filhodir(No *no) {
    No *novo = criar_no(no->valor1, no->pai);
    
    // O valor do meio sobe para o pai
    no->pai->valor2 = no->valor2;
    
    // Ajustando os filhos do pai
    no->pai->meio = novo;
    no->valor1 = no->valor2;
    no->valor2 = 0;
    no->tipo = 1;
    
    // Ajustando ponteiros
    novo->pai = no->pai;
}

// Função para dividir um nó cheio
void split_cheio(No *no) {
    if (no->tipo != 2) return;

    if (no->pai == NULL) {
        // Criando nova raiz
        raiz = criar_no(no->valor1, NULL);
        raiz->esq = no;
        raiz->dir = criar_no(no->valor2, raiz);
        no->pai = raiz;
        raiz->dir->pai = raiz;
    } else {
        if (no->pai->esq == no) {
            split_filhoesq(no);
        } else {
            split_filhodir(no);
        }
    }
}

// Inserção de valor em um nó
void inserir_valor(No *no, int num) {
    if (no->tipo == 1) {
        no->valor2 = num;
        ordenar(no);
        no->tipo = 2;
    } else {
        no->valortemp = num;
        split_cheio(no);
    }
}

// Função para inserir na árvore 2-3
void inserir_no(int num) {
    if (raiz == NULL) {
        raiz = criar_no(num, NULL);
        return;
    }

    No *pos = raiz;
    while (pos->esq != NULL) {
        if (num < pos->valor1) {
            pos = pos->esq;
        } else if (pos->tipo == 2 && num > pos->valor2) {
            pos = pos->dir;
        } else {
            pos = pos->meio;
        }
    }
    inserir_valor(pos, num);
}

// Função para imprimir a árvore (pré-ordem)
void imprimir(No *no, int nivel) {
    if (no == NULL) return;
    
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("[%d", no->valor1);
    if (no->tipo == 2) printf(", %d", no->valor2);
    printf("]\n");
    
    imprimir(no->esq, nivel + 1);
    imprimir(no->meio, nivel + 1);
    imprimir(no->dir, nivel + 1);
}

int main() {
    inserir_no(10);
    inserir_no(20);
    inserir_no(5);
    inserir_no(30);
    inserir_no(25);
    
    printf("Árvore 2-3:\n");
    imprimir(raiz, 0);
    
    return 0;
}
