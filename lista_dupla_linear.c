#include <stdio.h>
#include <stdlib.h>

#define null NULL

typedef struct elemento Elemento;
struct elemento
{
    int valor;
    Elemento *proximo;
    Elemento *anterior; 
};

Elemento *inicio;
Elemento *fim;
int tamanho;

void criarLista();
Elemento *aloca(int valor);
void insereInicio(int valor);
void insereFim(int valor);
void inserePosicao(int valor, int posicao);
void removeInicio();
void removeFim();
void imprimeLista();
void imprimeListaContrario();

void criarLista()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

Elemento *aloca(int valor)
{
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->valor = valor;
    novo->proximo = null;
    novo->anterior = null;
    return novo;
}

void removeInicio()
{
    Elemento *atual = inicio;
    inicio = atual->proximo;
    inicio->anterior = null;
    tamanho--;
}

void removeFim()
{
    Elemento *atual = fim;
    fim = atual->anterior;
    fim->proximo = null;
    tamanho--;
}

void insereInicio(int valor)
{
    Elemento *novo = aloca(valor);
    if(inicio == null)
    {
        inicio=novo;
        fim=novo;

    }
    else
    {
        Elemento *atual;
        atual = inicio;
        novo->proximo = atual;
        atual->anterior = novo;
        inicio = novo;
    }
    tamanho++;
}

void insereFim(int valor)
{
    Elemento *novo = aloca(valor);
    if(inicio == null)
    {
        inicio = novo;
        fim = novo;
    }
    else
    {
        Elemento *atual;
        atual = fim;
        novo->anterior = atual;
        atual->proximo = novo;
        fim = novo;
    }
    tamanho++;
}

void inserePosicao(int valor, int posicao)
{
    posicao = posicao-1;
    Elemento *novo = aloca(valor);

    if(inicio == null)
    {
        inicio = novo;
        fim = novo;
    }
    else
    {
        Elemento *atual, *tmp;
        int i;

        if(posicao < (tamanho/2))
        {
            atual = inicio;
            i = 0;
        }
        else
        {
            atual = fim;
            i = tamanho;
        }

        while(i != posicao && i >= 0 && i <= tamanho)
        {
            if(i < posicao)
            {
                i++;
                atual = atual->proximo;
            }
            else if (i > posicao)
            {
                i--;
                atual = atual->anterior;
            }

            if(posicao == i)
            {
                printf("Valor antecessor ao quero inserir %d\n", atual->anterior->valor);
                printf("Valor proximo ao quero inserir %d\n", atual->proximo->valor);
            }

        }

    }
}

void imprimeLista()
{
    Elemento *atual;
    atual = inicio;
    while(atual)
    {
        printf("%d\n", atual->valor);
        atual = atual->proximo;
    }
}

void imprimeListaContrario()
{
    Elemento *atual;
    atual = fim;
    while(atual)
    {
        printf("%d\n", atual->valor);
        atual = atual->anterior;
    }
}

int main()
{
    criarLista();
    int i;
    for(i = 0; i < 5; i++)
    {
        insereInicio(i);
    }
    inserePosicao(10, 2);
    imprimeLista();
    printf("---------------\n");
    imprimeListaContrario();
}