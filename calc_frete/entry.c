/*
*   Shipping calculator source code
*   by Victor Maciel, Daniel Araujo, Lucas Simoes and Miguel Leite
*   Created 21/10/24
*   Last Edit: 30/10/24
*
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

// Defines
#define     VERSION                         "0.2"

#define     MAX_BLOCK_WORD_LEN              (16+1)
#define     MAX_INPUT_TEXT                  (64+1)

#define     MULTIPLIER_SOUTH_N_SOUTHEAST    0.25f
#define     MULTIPLIER_NORTH_N_NORTHEAST    0.50f

#define     MAX_ITEMS                       (INVALID_ITEM_ID)
#define     MAX_ITEM_NAME                   (64+1)
#define     ITEM_ALL                        INVALID_ITEM_ID
#define     INVALID_ITEM_ID                 0xFF         

#define WAIT_FOR_INPUT() getchar(); getchar();
#if __WIN32 
    #define cls system("cls"); 
#else 
    #define cls system("clear"); 
#endif

// Functions

void ShowItems(unsigned char itemid); // itemid 0 - 254 
void ShowAdvices();

struct ItemData 
{
    char itemName[MAX_ITEM_NAME];
    float itemPrice;
    int itemQuantity;
};

struct ItemData g_Items[MAX_ITEMS] = 
{
    {"Tv", 195.90, 3},
    {"Refrigerador", 799.90, 2},
    {"Microondas", 299.90, 1}
};

char g_BlockedWords[][MAX_BLOCK_WORD_LEN] =
{
    "Finalizar",
    "Carrinho",
    "Remover"
};

unsigned char g_Cart[MAX_ITEMS];

int main()
{
    char inputtext[MAX_INPUT_TEXT];

    ShowAdvices();

    ScanPrompt(&inputtext);

    return 0;
}

void ScanPrompt(const char *inputtext)
{
    unsigned char number, i, j, name;

    for(i = 0; i < MAX_ITEMS; i++)
    {
        if(sscanf(inputtext, "%d", &number) && IsValidItemId(number)) return AddItemToCart(number);

        for(j = 0; j < MAX_ITEM_NAME; j++)
        {
            tolower(inputtext[j]);
            strcpy(&name, g_Items[i].itemName);
            tolower(name);
        }

        if(!strcmp(inputtext, g_Items[i].itemName) && IsValidItemId(i)) return AddItemToCart(i);
    }

    return;
}

int IsValidItemId(unsigned char itemid)
{
    if(itemid != INVALID_ITEM_ID && strlen(g_Items[itemid].itemName)) return 1;
    else return 0;
}

void ShowAdvices()
{
    #define MAX_OUTPUT_MESSAGE (128+1)
    char i, messages[][MAX_OUTPUT_MESSAGE] =
    {
        "-> Digite o numero ou o nome de algum item para adicionar ao carrinho.",
        "-> Digite Finalizar para confirmar o carrinho.",
        "-> Digite \"Carrinho\" para visualizar seu carrinho.",
        "-> Digite \"Remover + (nome ou numero)\" para remove-lo de seu carrinho. Ex: Remover Tv"
    };

    for(i = 0; i < (sizeof(messages) / (MAX_OUTPUT_MESSAGE)); i++)
    {
        puts(messages[i]);
    }

    return;
    #undef MAX_OUTPUT_MESSAGE
}

void ShowItems(const unsigned char itemid)
{
        if(!IsValidItemId(itemid)) printf("Erro no sistema: Item %s (%d) Inexistente!", g_Items[itemid].itemName, itemid);
        
        printf(
            ">>> Item: (%d) <<<\n"
            ">>> Nome Item: (%s) <<<\n"
            ">>> Preco: (%0.2f) <<<\n"
            ">>> Quantidade: (%d) <<<\n",
        itemid, g_Items[itemid].itemName, g_Items[itemid].itemPrice, g_Items[itemid].itemQuantity);
        return;
    }

    unsigned char i; // Avoidar o erro de C99 

    for(i = 0; i < MAX_ITEMS; i++)
    {
        if(strlen(g_Items[i].itemName) <= 0) continue;
        printf(
            ">>> Item: (%d) <<<\n"
            ">>> Nome Item: (%s) <<<\n"
            ">>> Preco: (%0.2f) <<<\n"
            ">>> Quantidade: (%d) <<<\n",
        i, g_Items[i].itemName, g_Items[i].itemPrice, g_Items[i].itemQuantity);
    }

    return;
}
