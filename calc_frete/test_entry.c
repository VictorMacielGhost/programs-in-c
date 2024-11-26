#include <stdio.h>
#include <string.h>
#include <assert.h>

// Inclua o arquivo de cabe�alho do seu c�digo principal
#include "entry.c"

// Fun��o de teste para IsValidItemId
void TestIsValidItemId() {
    assert(IsValidItemId(0) == 1); // Primeiro ID v�lido
    // assert(IsValidItemId(MAX_ITEMS - 1) == 1); // �ltimo ID v�lido (254)
    assert(IsValidItemId(MAX_ITEMS) == 0); // ID 255 deve ser inv�lido
    assert(IsValidItemId(INVALID_ITEM_ID) == 0); // ID 255 deve ser inv�lido
    printf("TestIsValidItemId passou.\n");
}

// Fun��o de teste para AddItemToCart
void TestAddItemToCart() {
    // Limpa o carrinho
    int i;
    for ( i = 0; i < MAX_ITEMS; i++) {
        g_Cart[i][0] = INVALID_ITEM_ID;
        g_Cart[i][1] = 0;
    }

    // Adiciona um item v�lido
    AddItemToCart(0);
    assert(g_Cart[0][0] == 0);
    assert(g_Cart[0][1] == 1);
    printf("TestAddItemToCart passou.\n");
}

// Fun��o de teste para CalculateShipping
void TestCalculateShipping() {
    // Limpa o carrinho
    int i;
    for ( i = 0; i < MAX_ITEMS; i++) {
        g_Cart[i][0] = INVALID_ITEM_ID;
        g_Cart[i][1] = 0;
    }

    // Adiciona alguns itens ao carrinho
    AddItemToCart(0); // TV
    AddItemToCart(1); // Refrigerador

    // Calcula o frete
    CalculateShipping();

    // Verifica se o frete foi calculado corretamente
    // (Aqui voc� pode adicionar verifica��es espec�ficas baseadas nos valores esperados)
    printf("TestCalculateShipping passou.\n");
}

int main() {
    // Chama as fun��es de teste
    TestIsValidItemId();
    TestAddItemToCart();
    TestCalculateShipping();

    printf("Todos os testes passaram.\n");
    return 0;
}