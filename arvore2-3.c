#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor1, valor2, valortemp;
    struct No *esq, *meio, *dir, *pai;
    int tipo, n_valor; //0: folha // 1: 2 filhos // 2: 3 filhos
}No;

No *raiz = NULL;

No *ordenar (No *no){
    if (no->valor1>no->valor2)
    {
        int temp = no->valor1;
        no->valor1 = no->valor2;
        no->valor2 = temp;
    }
    return no;
} //garante que o nó sempre tenha o menor valor no espaço 1 e o maior no espaço 2

No *reorganizar (No *no){
    int temp;
    if (no->valortemp < no->valor1)
    {
        temp = no->valor1;
        no->valor1 = no->valortemp;
        no->valortemp = no->valor2;
        no->valor2 = temp;
    } else {
        if (no->valortemp < no->valor2)
        {
            temp = no->valor2;
            no->valor2 = no->valortemp;
            no->valortemp = temp;
        }
    }
    return no;
} //garante que o nó prestes a sofrer um split sempre seja organizado como: menor = valor1; médio = valor2; maior = valortemp

No *criar_no (No *pai, int num){
    No *novo = (No*) malloc(sizeof(No));
    novo->n_valor = 0;
    novo->valor1 = num;
    novo->valor2 = 0;
    novo->tipo = 0;
    novo->pai = pai;
    novo->esq = novo->dir = novo->meio = NULL;
    novo->n_valor++;
    return novo;
} //cria um nó caso o ponteiro aponte para um espaço para inserir e ele esteja nulo

void split (No *no, int num){
    no->valortemp = num;
    no = reorganizar(no);
    no->esq = criar_no(no, no->valor1);
    no->valor1 = no->valor2;
    no->dir = criar_no(no, no->valortemp);
    no->valor2 = 0;
    no->n_valor = 1;
    no->tipo = 1; //agora o nó tem 1 valor e 2 filhos
} //dá split caso um nó que não possui filhos encha, exceto caso esse seja filho de uma 1-2

void split2 (No *no, int num){
    if (no->pai->tipo == 2)
    {
        split(no->pai, num);
    } else {
        no->valortemp = num;
        no = reorganizar(no);
        no->pai->valor2 = no->valor2;
        no->pai = ordenar(no->pai);
        if (num < no->pai->valor1)
        {
            no->pai->meio = criar_no(no->pai, no->valortemp);
        } else {
            no->pai->meio = criar_no(no->pai, no->valor1);
            no->valor1 = no->valortemp;
        }
        no->valor2 = 0;
        no->n_valor--;
        no->pai->tipo = 2; //agora o pai tem 2 valores e 3 valores
    }
} //dá split caso o filho de 1-2 encha

No *inserir_valor (No *no, int num){
    if (no->n_valor == 1)
    {
        no->valor2 = num;
        no->n_valor++;
        no = ordenar(no);
    } else {
        if (no->pai == NULL || (no->pai->tipo == 0 || no->pai->tipo == 2)){
        split(no, num);
    } else {
            split2(no, num);
        }
    }
    return no;
}

void local_insercao (No *certo, int num){
    if (certo->tipo == 0)
    {
        certo = inserir_valor(certo, num);
        return;
    }
    if (certo->tipo == 1)
    {
        if (certo->valor1>num)
        {
            local_insercao(certo->esq, num);
        } else {
            local_insercao(certo->dir, num);
        }
        return;
    }

    if (certo->tipo == 2) {
        if (num < certo->valor1) {
            local_insercao(certo->esq, num);
        } else if (num > certo->valor2) {
            local_insercao(certo->dir, num);
        } else {
            local_insercao(certo->meio, num);
        }
    }
}

void inserir (int num){
    if (raiz==NULL)
    {
        raiz = criar_no(NULL, num);
    } else {
        local_insercao(raiz, num);
    }
}

No* busca(No* encontrado, int num) {
    if (encontrado == NULL) return NULL;

    if (encontrado->valor1 == num || encontrado->valor2 == num) {
        return encontrado;
    }

    No *res = busca(encontrado->esq, num);
    if (res != NULL) return res;

    res = busca(encontrado->meio, num);
    if (res != NULL) return res;

    res = busca(encontrado->dir, num);
    if (res != NULL) return res;

    return NULL;
}

void buscar (int num){
    if (busca(raiz, num) == NULL) {
        printf("\nValor %d não encontrado!\n", num);
        return;
    } else {
        printf("\nValor %d encontrado!\n", num);
    }
}

No *fusao (No *no){
    if (no->dir == NULL)
    {
        no->dir = criar_no(no->dir, no->meio->valor1);
        no->dir = inserir_valor(no->dir, no->valor2);
        no->valor2 = 0;
        free(no->meio);
    }

    if (no->meio == NULL)
    {
        if (no->esq->tipo == 0)
        {
            no->esq = inserir_valor(no->esq, no->valor1);
            no->valor1 = no->valor2;
            no->valor2 = 0;
        } else {
            no->dir = inserir_valor(no->dir, no->valor2);
            no->valor2 = 0;
        }
    }

    if (no->esq == NULL)
    {
        no->esq = criar_no(no->esq, no->valor1);
        no->esq = inserir_valor(no->esq, no->meio->valor1);
        no->valor1 = no->valor2;
        no->valor2 = 0;
        free(no->meio);
    }
    no->tipo = 1;
}

No *ajuste_posdel (No *no){
    int temp1, temp2;
    if (no->tipo == 1){
        if (no->dir == NULL)
        {
            if (no->esq->n_valor == 2)
            {
                no->dir = criar_no(no, no->valor1);
                no->valor1 = no->esq->valor2;
                no->esq->valor2 = 0;
                no->esq->n_valor--;
            } else {
                no->valor2 = no->valor1;
                no->valor1 = no->esq->valor1;
                no->esq = NULL;
                no->n_valor = 2;
                no->tipo = 0;
            }
        } else {
        if (no->esq == NULL)
        {
            if (no->dir->n_valor == 2)
            {
                no->esq = criar_no(no, no->valor1);
                no->valor1 = no->esq->valor2;
                no->esq->valor2 = 0;
                no->esq->n_valor--;
            } else {
                no->valor2 = no->dir->valor1;
                no->dir = NULL;
                no->n_valor = 2;
                no->tipo = 0;
            }
        }}
    }

    if (no->tipo == 2)
    {
        if (no->n_valor == 1 && ((no->meio != NULL && no->esq != NULL) && no->dir != NULL))
        {
            no = ordenar(no);
            if (no->esq->valor2 != 0)
            {
                no->valor2 = no->valor1;
                no->valor1 = no->esq->valor2;
                no->esq->valor2 = 0;
            } else {

                if (no->dir->valor2 != 0)
                {
                    no->valor2 = no->dir->valor1;
                    no->dir->valor1 = no->dir->valor2;
                    no->dir->valor2 = 0;

                } else {
                    if (no->meio->valor2 != 0)
                    {
                        if (no->meio->valor2 < no->valor1)
                        {
                            no->valor2 = no->valor1;
                            no->valor1 = no->meio->valor1;
                            no->meio->valor1 = no->meio->valor2;
                            no->meio->valor2 = 0;
                        } else {
                            no->valor2 = no->meio->valor2;
                            no->meio->valor2 = 0;
                        } 
                    } else {
                        if (no->meio->valor1 < no->valor1)
                        {
                            no->dir->valor2 = no->dir->valor1;
                            no->dir->valor1 = no->valor1;
                            no->valor1 = no->meio->valor1;
                            free(no->meio);
                            no->meio = NULL;
                            no->tipo = 1;
                        } else {
                            no->esq->valor2 = no->valor1;
                            no->valor1 = no->meio->valor1;
                            free(no->meio);
                            no->meio = NULL;
                            no->tipo = 1;
                        }
                    }
                }
            }
        }
        
        if (no->esq == NULL)
        {
            no->esq = criar_no(no->esq, no->valor1);
            if (no->meio->n_valor == 2 && no->dir->n_valor == 1)
            {
                no->valor1 = no->meio->valor1;
                no->meio->valor1 = no->meio->valor2;
                no->meio->valor2 = 0;
                no->meio->n_valor--;
            } else {
                if (no->dir->n_valor == 2)
                {
                    no->valor1 = no->valor2;
                    no->valor2 = no->dir->valor1;
                    no->dir->valor1 = no->dir->valor2;
                    no->dir->valor2 = 0;
                    no->dir->n_valor--;
                } else {
                    no = fusao(no);
                }
            }
        }
    
        if (no->dir == NULL)
        {
            no->dir = criar_no(no->dir, no->valor2);
            if (no->meio->n_valor == 2)
            {
                no->valor2 = no->meio->valor2;
                no->meio->valor2 = 0;
                no->meio->n_valor--;
            } else {
                if (no->esq->n_valor == 2)
                {
                    no->valor2 = no->valor1;
                    no->valor1 = no->esq->valor2;
                    no->esq->valor2 = 0;
                    no->esq->n_valor--;
                } else {
                    no = fusao(no);
                }
            }
        }
        
        if (no->meio == NULL){
            if (no->esq->n_valor == 2)
            {
                no->meio = criar_no(no, no->valor1);
                no->valor1 = no->esq->valor2;
                no->esq->valor2 = 0;
                no->esq->n_valor--;
            } else {
                if (no->dir->n_valor == 2)
                {
                    no->meio = criar_no(no, no->valor2);
                    no->valor2 = no->dir->valor1;
                    no->dir->valor1 = no->dir->valor2;
                    no->dir->valor2 = 0;
                    no->dir->n_valor--;
                } else {
                    no = fusao(no);
                }
            }
        }
    }
    return no;
}

void deletar_valor (int num){
    No *local = busca(raiz, num);
    if (local != NULL)
    {
        No *pai = local->pai;
            if (local->n_valor == 2)
            {

                if (local->valor1 == num)
                {
                    local->valor1 = local->valor2;
                }

                local->valor2 = 0;
                local->n_valor = 1;

                if (local->meio != NULL)
                {
                    local = ajuste_posdel(local);
                }
                
            } else {
                local->valor1 = 0;
                local->n_valor = 0;

                if (local->tipo == 1)
                {
                    local->valor1 = local->esq->valor1;
                    local->valor2 = local->dir->valor1;
                    local->n_valor = 2;
                    local->esq = NULL;
                    local->dir = NULL;
                }
                
                if (local->tipo == 0)
                {
                    if (pai->esq == local) pai->esq = NULL;
                    if (pai->meio == local) pai->meio = NULL;
                    if (pai->dir == local) pai->dir = NULL;
                    pai = ajuste_posdel(pai);
                }

                }
            } else return;
}

void imprimir_no (No *no){
    if (no != NULL)
    {
        printf (" [%d] ", no->valor1);
        if (no->valor2 != 0)
        {
            printf ("[%d] ", no->valor2);
        }
        printf ("|");
    } else {
        return;
    }
}

void imprimir_nivel (No *no){
    int nivel = 0;
    if (no != NULL)
    {
        if (no==raiz)
        {
            imprimir_no(no);
            nivel = 1;
        }
    
        printf ("\n");
    
        if (no->tipo != 0)
        {
            imprimir_no(no->esq);
            imprimir_no(no->meio);
            imprimir_no(no->dir);
        } else {
            return;
        }
    
        imprimir_nivel(no->esq);
        imprimir_nivel(no->meio);
        imprimir_nivel(no->dir);

    } else return;
}

int main (){
    inserir(5);
    inserir(2);
    inserir(6);
    inserir(4);
    inserir(7);
    inserir(8);
    inserir(3);
//    deletar_valor(6);
//    deletar_valor(5);
    imprimir_nivel(raiz);
    buscar(5);
}