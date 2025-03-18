#include <stdio.h>
#include <stdlib.h>

#define null NULL

typedef struct node
{
    struct ndoe *prox;
    struct node *ant;
    int valor; 
} TipoNode;

typedef struct lista
{
    TipoNode *inicio;
    int tamanho;
} Lista;

void FLVazia(Lista *lista)
{
    lista->inicio = null;
    lista->tamanho = 0;
}

int vazia(Lista lista)
{
    return lista.inicio == null;
}

void insereFim(int item, Lista *lista)
{
    if(vazia(*lista))
    {
        lista->inicio = malloc(sizeof(TipoNode));
        lista->inicio->valor = item;
        lista->inicio->prox = lista->inicio;
        lista->inicio->ant = lista->inicio;
    }
    else
    {
        TipoNode *ultimo = lista->inicio->ant;
        TipoNode *novo = malloc(sizeof(TipoNode));
        ultimo->prox = novo;
        novo->prox = lista->inicio;
        novo->ant = ultimo;
        lista->inicio->ant = novo;
        novo->valor = item;
    }
    lista->tamanho++;
}

void insere(int item, int pos, Lista *lista)
{
    if(pos > lista->tamanho)
    {
        printf("Impossive inserir pois posicao <%d> eh maior q o tamanho <%d>", pos, lista->tamanho);
    }
    else
    {
        TipoNode *novo = malloc(sizeof(TipoNode));
        novo->valor = item;
        novo->prox = null;

        if(pos == 1)
        {
            TipoNode *head = lista->inicio;
            novo->prox = head;
            lista->inicio = novo;
            lista->tamanho++;
        }

    }
}