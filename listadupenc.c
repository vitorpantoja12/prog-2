#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    int pos;
    struct No *prox;
    struct No *ant;
} No;

No *head = NULL;
No *tail = NULL;
int n_nos = 0;

void inserir_inicio (int num){
    No *novo = (No*) malloc (sizeof(No));
    if (novo == NULL){
        printf ("Erro!\n");
    } else {
        novo->valor = num;
        novo->pos = 1;
        novo->prox = head;
        novo->ant = NULL;
        if (head!=NULL)
        {
            head->ant = novo;
        }
        head = novo;        
        No *temp = head->prox;
        while (temp!=NULL)
        {
            temp->pos=temp->pos+1;
            temp=temp->prox;
        }
        n_nos++;
    }
}

void inserir_final (int num){
    if (head == NULL)
    {
        inserir_inicio(num);
        tail = head;
        return;
    }
    No *novo = (No*) malloc (sizeof(No));
    if (novo == NULL)
    {
        printf ("Erro!\n");
    } else {
        novo->valor = num;
        tail = head;
        while (tail->prox!=NULL)
        {
            tail = tail->prox;
        }
        novo -> prox = NULL;
        novo -> ant = tail;
        novo->pos = tail->pos + 1;
        tail->prox = novo;
        tail = novo;
        n_nos++;
    } 
}

void inserir_determinado (int posn, int num){
    No *novo = (No*) malloc (sizeof(No));
    if (novo == NULL){
        printf ("Erro!\n");
    } else {
        novo->valor = num;
        novo->pos = posn;
        No *nprox = head;
        while (nprox->pos!=posn)
        {
            nprox=nprox->prox;
        }
            novo->ant = nprox->ant;
            nprox->ant->prox = novo;
            novo->prox = nprox;
            nprox->ant = novo;
        No *temp = nprox;
        while (temp!=NULL)
        {
            temp->pos=temp->pos+1;
            temp=temp->prox;
        }
        n_nos++;
    }
}

void deletar_dtm (int posd){
    No *deletado = head;
    while (deletado->pos!=posd)
    {
        deletado=deletado->prox;
    }
    No *temp = deletado->prox;
        deletado->ant->prox = deletado->prox;
        deletado->prox->ant = deletado->ant;
    while (temp!=NULL)
    {
        temp->pos=temp->pos-1;
        temp=temp->prox;
    }
    free (deletado);
    n_nos--;
}

void deletar_inicio (){
    No *deletado = head;
    head = deletado->prox;
    head->ant = NULL;
    No *temp = head;
    while (temp!=NULL)
    {
        temp->pos=temp->pos-1;
        temp=temp->prox;
    }
    free (deletado);
    n_nos--;
}

void deletar_final (){
    No *deletado = tail;
    tail = deletado->ant;
    tail->prox = NULL;
    free (deletado);
    n_nos--;
}

void buscar (int num){
    No *temp = head;
    while (temp->valor!=num)
    {
        temp=temp->prox;
    }
    printf ("Nó [%d], localizado na posição (%d).", temp->valor, temp->pos);
}

void imprimir_direto (){
    No *temp = head;
    while (temp != NULL){
        printf ("[%d] (%d) \n", temp->valor, temp->pos);
        temp = temp->prox;
    }
    printf ("\n");
}

void imprimir_reverso (){
    No *temp = tail;
    while (temp != NULL){
        printf ("\n[%d] (%d)", temp->valor, temp->pos);
        temp = temp->ant;
    }
    printf ("\n");
}

int main (){
    int opc;
    printf ("Selecione uma opção: \n1. Criar lista \n2. Sair\n");
    scanf ("\n%d", &opc);
    if (opc==1)
    {
        printf ("1. Adicionar nó no ínicio                  2. Adicionar nó no final                   3. Adicionar nó em posição específica\n");
        printf ("4. Deletar nó do ínicio                    5. Deletar nó no final                     6. Deletar nó em posição específica\n");
        printf ("7. Buscar nó                               8. Fechar");
    }
}