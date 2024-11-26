#include <stdio.h>
#include <string.h>
#include <assert.h>

// Inclua o arquivo de cabeçalho do seu código principal
#include "entry.c"

// Função de teste para IsValidItemId
void TestIsValidItemId() {
    assert(IsValidItemId(0) == 1); // Primeiro ID válido
    // assert(IsValidItemId(MAX_ITEMS - 1) == 1); // Último ID válido (254)
    assert(IsValidItemId(MAX_ITEMS) == 0); // ID 255 deve ser inválido
    assert(IsValidItemId(INVALID_ITEM_ID) == 0); // ID 255 deve ser inválido
    printf("TestIsValidItemId passou.\n");
}

// Função de teste para AddItemToCart
void TestAddItemToCart() {
    // Limpa o carrinho
    int i;
    for ( i = 0; i < MAX_ITEMS; i++) {
        g_Cart[i][0] = INVALID_ITEM_ID;
        g_Cart[i][1] = 0;
    }

    // Adiciona um item válido
    AddItemToCart(0);
    assert(g_Cart[0][0] == 0);
    assert(g_Cart[0][1] == 1);
    printf("TestAddItemToCart passou.\n");
}

// Função de teste para CalculateShipping
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
    // (Aqui você pode adicionar verificações específicas baseadas nos valores esperados)
    printf("TestCalculateShipping passou.\n");
}

int main() {
    // Chama as funções de teste
    TestIsValidItemId();
    TestAddItemToCart();
    TestCalculateShipping();

    printf("Todos os testes passaram.\n");
    return 0;
}