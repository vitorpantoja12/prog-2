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
        if (posn<n_nos)
        {
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
        } else {
            if (posn==1)
            {
                inserir_inicio(num);
            } else {
                if (posn >= n_nos+1){
                    inserir_final(num);}
            }
        }
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
    printf ("\nNó [%d], localizado na posição (%d).\n", temp->valor, temp->pos);
}

void imprimir_direto (){
    No *temp = head;
    while (temp != NULL){
        printf ("[%d] ", temp->valor);
        temp = temp->prox;
    }
    printf ("\n");
}

void imprimir_reverso (){
    No *temp = tail;
    while (temp != NULL){
        printf ("\n[%d] ", temp->valor);
        temp = temp->ant;
    }
    printf ("\n");
}

void menu_imprimir() {
    int opc = 0;
    printf("\n1. Imprimir direto\n");
    printf("2. Imprimir reverso\n");
    printf("Opção: ");
    scanf("%d", &opc);
    
    if (opc == 1) {
        imprimir_direto();
    } else if (opc == 2) {
        imprimir_reverso();
    } else {
        printf("\nOpção inválida.\n");
    }
}

void menu_inserir() {
    int opc = 0, num, pos;
    
    printf("\n1. Inserir no início\n");
    printf("2. Inserir em uma posição específica\n");
    printf("3. Inserir no final\n");
    printf("Opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("Digite o número: ");
            scanf("%d", &num);
            inserir_inicio(num);
            break;
        case 2:
            printf("Digite o número e a posição: ");
            scanf("%d %d", &num, &pos);
            inserir_determinado(pos, num);
            break;
        case 3:
            printf("Digite o número: ");
            scanf("%d", &num);
            inserir_final(num);
            break;
        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

void menu_deletar() {
    int opc = 0, pos;
    
    printf("\n1. Deletar do início\n");
    printf("2. Deletar de uma posição específica\n");
    printf("3. Deletar do final\n");
    printf("Opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            deletar_inicio();
            break;
        case 2:
            printf("Digite a posição: ");
            scanf("%d", &pos);
            deletar_dtm(pos);
            break;
        case 3:
            deletar_final();
            break;
        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

int main() {
    int opc = 0;

    do {
        printf("\nSelecione uma opção:\n");
        printf("1. Inserir na lista\n");
        printf("2. Deletar da lista\n");
        printf("3. Imprimir\n");
        printf("4. Buscar na lista\n");
        printf("5. Fechar\n");
        printf("Opção: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                menu_inserir();
                break;
            case 2:
                menu_deletar();
                break;
            case 3:
                menu_imprimir();
                break;
            case 4:
                int numbusc = 0;
                printf ("Digite o valor a ser buscado: \n");
                scanf ("%d", &numbusc);
                buscar(numbusc);
                break;
            case 5:
                break;
            default:
                printf("\nOpção inválida.\n");
                break;
        }
    } while (opc != 5);

    return 0;
}