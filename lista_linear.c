#include <stdio.h>
#include <stdlib.h>


typedef struct tipo_produto // define a struct tipo_produto
{
    int codigo;
    double preco;
    struct tipo_produto *proximo; // cria um ponteiro para o proximo produto //? mas pq do tipo struct tipo_produto?
} TProduto; // define o tipo TProduto como a struct tipo_produto

void inserir(TProduto **cabeca); //? pq **cabeca? ponteiro de ponteiro?
void listar(TProduto *cabeca); 

int main() {
    
    TProduto *cabeca = NULL; // pq *cabeca? //* os dados passados pra essa variaveis sao referencias q serao utilizadas internamente na funcao
    TProduto *noatual; // pq *noatual?
    char q;

    do
    {
        printf("\n\nOpcoes: \nI -> para inserir novo produto;\nL -> para listar produtos;\nS -> para sair;\n");
        scanf("%c", &q);
        switch(q)
        {
            case 'i': case 'I': inserir(&cabeca); break;
            case 'l': case 'L': listar(cabeca); break;
            case 's': case 'S': break;
            default: printf("Opcao invalida!\n");
        }
        fflush(stdin);
    } while (q!='s' && q!='S');

    noatual = cabeca;
    while(noatual != NULL)
    {
        cabeca = noatual->proximo;
        free(noatual);
        noatual = cabeca;
    }

    return 0;
}

void listar(TProduto *noatual)
{
    int i = 0;
    while(noatual != NULL)
    {
        i++;
        printf("\nProduto %d: \nCodigo: %d\nPreco: %.2f\n", i, noatual->codigo, noatual->preco);
        noatual = noatual->proximo;
    }
}

void inserir(TProduto **cabeca) // essa variavel eh um ponteiro q aponta pra um ponteiro, esse ponteiro aponta pra onde  os dados estao
{
    TProduto *noatual, *novono;
    int cod;
    double preco;
    printf("\n Codigo do novo produto: ");
    scanf("%d", &cod);
    printf("\n Preco do novo produto: ");
    scanf("%lf", &preco);
    if(*cabeca == NULL) // se o ponteiro apontar pra NULL (for a primeira vez inserindo)
    {
        *cabeca = (TProduto *) malloc(sizeof(TProduto)); // cria um espaco pra produto
        (*cabeca)->codigo = cod; 
        (*cabeca)->preco = preco;
        (*cabeca)->proximo = NULL;
        // cria o primeiro elemento da lista (vulgo, o final)
    }
    else
    {
        noatual = *cabeca;
        while(noatual->proximo != NULL)
        {
            noatual = noatual->proximo;
        }
        novono = (TProduto *) malloc(sizeof(TProduto));
        novono->codigo = cod;
        novono->preco = preco;
        novono->proximo = NULL;
        noatual->proximo = novono;
    }
}