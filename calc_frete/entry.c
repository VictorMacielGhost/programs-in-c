/*
*   Shipping calculator source code
*   by Victor Maciel, Daniel Araujo, Lucas Simoes and Miguel Leite
*   Created 21/10/24
*   Last Edit: 26/11/24
*
*   This program calculates shipping costs for various items. It allows users to add items to a cart, view the cart, and calculate the shipping cost based on the total weight of the items and the delivery region.
*
*   Libraries:
*   - stdio.h: Standard input/output library.
*   - stdlib.h: Standard library for memory allocation, process control, conversions, etc.
*   - string.h: Library for string handling functions.
*   - locale.h: Library for localization settings.
*   - ctype.h: Library for character handling functions.
*   - time.h: Library for time and date functions.
*
*   Defines:
*   - VERSION: Version of the program.
*   - MAX_INPUT_TEXT: Maximum length of input text.
*   - MAX_ITEMS: Maximum number of items.
*   - MAX_ITEM_NAME: Maximum length of item name.
*   - ITEM_ALL: Constant to represent all items.
*   - INVALID_ITEM_ID: Constant to represent an invalid item ID.
*   - HEAVY_ITEM_WEIGHT: Weight threshold for heavy items.
*   - WAIT_FOR_INPUT: Macro to wait for user input.
*   - cls: Macro to clear the console screen.
*   - DEBUG_LOG: Macro for logging debug information.
*
*   Functions:
*   - IsValidItemId: Checks if an item ID is valid, based on its name.
*   - AddItemToCart: Adds an item to the cart.
*   - ShowItems: Displays items based on the item ID.
*   - ShowCommands: Displays available commands.
*   - ScanPrompt: Scans user input and processes commands.
*   - CalculateShipping: Calculates the shipping cost based on the items in the cart and the delivery region.
*
*   Enums:
*   - ShippingType: Enum for different shipping costs based on region and item weight.
*
*   Structs:
*   - ItemData: Struct to store item information (name, price, weight, quantity).
*
*   Global Variables:
*   - g_Items: Array of ItemData structs to store available items.
*   - g_Cart: 2D array to store items in the cart and their quantities.
*   - g_Encerrar: Flag to indicate if the program should terminate.
*
*   Main Function:
*   - Initializes the cart and locale settings.
*   - Displays the program version and available commands.
*   - Continuously scans user input and processes commands until the program is terminated.
*/

// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

// Defines

#define     VERSION                         "1.0.3"
// #define     DEBUG
#define     MAX_INPUT_TEXT                  (64+1)                      // 64 characters + 1 for null terminator

#define     MAX_ITEMS                       (INVALID_ITEM_ID)           // 255
#define     MAX_ITEM_NAME                   (64+1)                      // 64 characters + 1 for null terminator
#define     ITEM_ALL                        INVALID_ITEM_ID             // 255
#define     INVALID_ITEM_ID                 0xFF                        // 255

#define     HEAVY_ITEM_WEIGHT               (2000.0f)                   // 2kg in grams

#define WAIT_FOR_INPUT() getchar();
#if __WIN32 
    #define cls system("cls"); 
#else 
    #define cls system("clear"); 
#endif

#if defined DEBUG
    #define DEBUG_LOG(fmt, ...) printf("DEBUG: " fmt, ##__VA_ARGS__)
#else
    #define DEBUG_LOG(fmt, ...) 
#endif

// Functions

int IsValidItemId(unsigned char itemid);
void AddItemToCart(unsigned char itemid);
void ShowItems(const unsigned char itemid);                                 // itemid 0 - 254 // 255 = ALL
void ShowCommands();
void ScanPrompt(char *inputtext);
void CalculateShipping();

enum ShippingType
{
    SHIPPING_DEFAULT_SOUTH = 30,
    SHIPPING_DEFAULT_SOUTHEAST = 25,
    SHIPPING_DEFAULT_NORTH = 35,
    SHIPPING_DEFAULT_NORTHEAST = 40,
    SHIPPING_HEAVY_SOUTH = 50,
    SHIPPING_HEAVY_SOUTHEAST = 45,
    SHIPPING_HEAVY_NORTH = 55,
    SHIPPING_HEAVY_NORTHEAST = 60
};

struct ItemData 
{
    char itemName[MAX_ITEM_NAME];
    float itemPrice, itemWeight;
    int itemQuantity;
};

struct ItemData g_Items[MAX_ITEMS] = 
{
    {"TV", 195.90, 1000.0f, 3},
    {"Refrigerador", 799.90, 5000.0f, 2},
    {"Microondas", 299.90, 3000.0f, 1},
    {"Notebook", 1999.90, 2000.0f, 4},
    {"Smartphone", 999.90, 500.0f, 5},
    {"Tablet", 499.90, 400.0f, 6},
    {"Ventilador", 99.90, 2000.0f, 4},
    {"Cafeteira", 49.90, 1000.0f, 5},
    {"Liquidificador", 39.90, 1500.0f, 6},
    {"Batedeira", 99.90, 3000.0f, 3},
    {"Torradeira", 39.90, 1000.0f, 2},
    {"Chaleira", 29.90, 1000.0f, 1},
    {"Grill", 79.90, 2000.0f, 5},
    {"Mixer", 59.90, 1000.0f, 6},
    {"Fritadeira", 199.90, 5000.0f, 1},
    {"Cervejeira", 1299.90, 8000.0f, 3},
    {"Adega", 899.90, 7000.0f, 4},
    {"Desumidificador", 249.90, 4500.0f, 3},
    {"Chapinha", 79.90, 1200.0f, 2},
    {"Barbeador", 89.90, 800.0f, 3},
    {"Frigideira", 49.90, 1500.0f, 5},
    {"Rechaud", 99.90, 1200.0f, 3},
    {"Webcam", 129.90, 300.0f, 5},
    {"SSD", 249.90, 400.0f, 5},
    {"Gabinete", 199.90, 700.0f, 6},
    {"Filmadora", 899.90, 1200.0f, 5},
    {"Microfone", 299.90, 1000.0f, 3},
    {"Impressora", 249.90, 2000.0f, 5},
    {"Scanner", 129.90, 1500.0f, 6},
    {"Poltrona", 399.90, 8000.0f, 5},
    {"Guarda-Roupa", 799.90, 15000.0f, 2},
    {"Tapete", 129.90, 1500.0f, 3},
    {"Espelho", 199.90, 1000.0f, 2},
    {"Cortina", 59.90, 800.0f, 5},
    {"Travesseiro", 69.90, 1500.0f, 6},
    {"Cobertor", 79.90, 2000.0f, 3},
    {"Edredom", 99.90, 1500.0f, 4},
    {"Almofada", 39.90, 500.0f, 2},
    {"Puff", 149.90, 6000.0f, 1}
};

int g_Cart[MAX_ITEMS][2];
int g_Encerrar = 0;

int main()
{
    
    int i;
    char inputtext[MAX_INPUT_TEXT];

    for(i = 0; i < MAX_ITEMS; i++)
    {
        g_Cart[i][0] = INVALID_ITEM_ID;
        g_Cart[i][1] = 0;
    }

    #if __WIN32
        if(!setlocale(LC_ALL, "portuguese"))
        {
            printf("Erro ao configurar locale. Verifique as configurações do sistema.\n");
        }
    #else
        if(!setlocale(LC_ALL, "pt_BR.UTF-8"))
        {
            printf("Erro ao configurar locale. Verifique as configurações do sistema.\n");
        }
    #endif
        
    printf("Calculadora de Frete - Versão %s\n", VERSION);
    
    ShowCommands();

    while(!g_Encerrar)
        ScanPrompt(inputtext);

    return 0;
}

void ScanPrompt(char *inputtext) 
{
    printf("\nDigite um comando: ");
    fgets(inputtext, MAX_INPUT_TEXT, stdin);

    int i;
    for(i = 0; i < MAX_INPUT_TEXT; i++)
    {
        inputtext[i] = tolower(inputtext[i]);
        if(inputtext[i] == '\n' || inputtext[i] == '\0')
        {
            inputtext[i] = '\0';
            break;
        }
    }

    if(g_Encerrar)
    {
        return;
    }

    if(strlen(inputtext) == 0)
    {
        printf("Nenhum comando digitado. Tente novamente.\n");
        return;
    }

    if(!strcmp(inputtext, "finalizar") || !strcmp(inputtext, "encerrar") || !strcmp(inputtext, "sair"))
    {
        printf("\nFinalizando carrinho...\n");
        g_Encerrar = 1;
        CalculateShipping();
        return;
    }
    else if(!strcmp(inputtext, "ajuda") || !strcmp(inputtext, "comandos") || !strcmp(inputtext, "help"))
    {
        ShowCommands();
        return;
    }
    else if(!strcmp(inputtext, "itens") || !strcmp(inputtext, "produtos") || !strcmp(inputtext, "lista"))
    {
        ShowItems(ITEM_ALL);
        return;
    }
    else if(!strcmp(inputtext, "carrinho") || !strcmp(inputtext, "cart") || !strcmp(inputtext, "pedido"))
    { 
        printf("\nCarrinho:\n");
        for(i = 0; i < MAX_ITEMS; i++)
        {
            if(g_Cart[i][0] != INVALID_ITEM_ID)
            {
                printf("Item: %s, Quantidade: %d\n", g_Items[g_Cart[i][0]].itemName, g_Cart[i][1]);
            }
        }
        return;
    }
    else if(strstr(inputtext, "remover"))
    {
        char *token = strtok(inputtext, " ");
        token = strtok(NULL, " ");

        if(!token || strlen(token) == 0)
        {
            printf("Comando inválido! Especifique o item a ser removido.\n");
            return;
        }

        for(i = 0; i < MAX_ITEMS; i++) // i is refference to the Item registered in the system. AKA ItemData 
        {
            DEBUG_LOG("Checking item: %s\n", g_Items[i].itemName);
            if(!strcasecmp(token, g_Items[i].itemName))
            {
                int j; // j is refference to the cart position of the item
                DEBUG_LOG("Found item in list: %s, ITEm ID %d\n", g_Items[i].itemName, i);
                for(j = 0; j < MAX_ITEMS; j++)
                {
                    if(g_Cart[j][0] == i) 
                    {
                        DEBUG_LOG("Item is in the cart: %s, Quantity: %d\n", g_Items[i].itemName, g_Cart[j][1]);
                        if(g_Cart[j][1] > 1)
                        {
                            g_Cart[j][1]--;
                            g_Items[i].itemQuantity++;
                            printf("Item %s removida 1 unidade do carrinho. %d unidades restantes!\n", g_Items[i].itemName, g_Cart[j][1]);
                            return;
                        }
                        else
                        {
                            g_Cart[j][0] = INVALID_ITEM_ID;
                            g_Cart[j][1]--;
                            g_Items[i].itemQuantity++;
                            printf("Item %s removido do carrinho!\n", g_Items[i].itemName);
                            return;
                        }
                    }
                } 
            }
        }
        printf("Item %s não está no carrinho!\n", token);
        return;
    }
    else if (strstr(inputtext, "adicionar"))
    {
        char *token = strtok(inputtext, " ");
        token = strtok(NULL, " ");

        if(!token || strlen(token) == 0)
        {
            printf("Comando inválido! Especifique o item a ser adicionado.\n");
            return;
        }

        for(i = 0; i < MAX_ITEMS; i++)
        {
            if(!strcasecmp(token, g_Items[i].itemName))
            {
                AddItemToCart(i);
                return;
            }
        }
        printf("Item %s não existente! Digite \"Itens\" para visualizar os itens disponíveis.\n", token);
        return;
    }
    else
    {
        printf("Comando inválido! Digite \"Comandos\" para visualizar os comandos disponíveis.\n");
        return;
    }
}

void ShowCommands()
{
    printf("\n==================== COMANDOS ====================\n");
    printf("-> \"Itens\"       - Ver lista de itens disponíveis.\n");
    printf("-> \"Carrinho\"    - Ver os itens no carrinho.\n");
    printf("-> \"Adicionar X\" - Adicionar item (Ex: Adicionar TV).\n");
    printf("-> \"Remover X\"   - Remover item (Ex: Remover TV).\n");
    printf("-> \"Finalizar\"   - Finalizar compra e calcular o frete.\n");
    printf("-> \"Comandos\"    - Mostrar esta lista de comandos.\n");
    printf("==================================================\n");
}


void AddItemToCart(unsigned char itemid)
{
    int i;

    if(!IsValidItemId(itemid))
    {
        printf("Erro: ID do item inválido!\n");
        return;
    }

    if(g_Items[itemid].itemQuantity <= 0)
    {
        printf("Erro: Estoque do item '%s' esgotado!\n", g_Items[itemid].itemName);
        return;
    }

    for(i = 0; i < MAX_ITEMS; i++)
    {
        if(g_Cart[i][0] == itemid)
        {
            g_Cart[i][1]++;
            g_Items[itemid].itemQuantity--;
            printf("Item '%s' adicionado ao carrinho! Estoque restante: %d\n",
                   g_Items[itemid].itemName, g_Items[itemid].itemQuantity);
            return;
        }

        else if(g_Cart[i][0] == INVALID_ITEM_ID)
        {
            g_Cart[i][0] = itemid;
            g_Cart[i][1] = 1;
            g_Items[itemid].itemQuantity--;
            printf("Item '%s' adicionado ao carrinho! Estoque restante: %d\n",
                   g_Items[itemid].itemName, g_Items[itemid].itemQuantity);
            return;
        }
        DEBUG_LOG("g_cart: %d, g_cart[i][0]: %d, g_cart[i][1]: %d\n", g_Cart[i], g_Cart[i][0], g_Cart[i][1]);
    }

    printf("Erro: Carrinho cheio!\n");
}

void ShowItems(const unsigned char itemid)
{
    unsigned char i;

    printf("\n==================== ITENS ====================\n");
    if(itemid == ITEM_ALL)
    {
        for(i = 0; i < MAX_ITEMS; i++)
        {
            if(IsValidItemId(i))
            {
                printf("ID: %d, Nome: %s, Preço: R$ %.2f, Peso: %.2fg, Estoque: %d\n",
                       i, g_Items[i].itemName, g_Items[i].itemPrice, g_Items[i].itemWeight, g_Items[i].itemQuantity);
            }
        }
    }
    else if(IsValidItemId(itemid))
    {
        printf("ID: %d, Nome: %s, Preço: R$ %.2f, Peso: %.2fg, Estoque: %d\n",
               itemid, g_Items[itemid].itemName, g_Items[itemid].itemPrice, g_Items[itemid].itemWeight, g_Items[itemid].itemQuantity);
    }
    else
    {
        printf("Erro: Item com ID %d não encontrado.\n", itemid);
    }
    printf("===============================================\n");
}

int IsValidItemId(unsigned char itemid)
{
    if(itemid != INVALID_ITEM_ID && strlen(g_Items[itemid].itemName)) return 1;
    else return 0;
}

void CalculateShipping()
{
    float totalWeight = 0.0f;
    float totalValue = 0.0f;
    float shippingValueSouth = 0.0f;
    float shippingValueSoutheast = 0.0f;
    float shippingValueNorth = 0.0f;
    float shippingValueNortheast = 0.0f;
    int i;
    int region;
    char inputtext[MAX_INPUT_TEXT];

    for(i = 0; i < MAX_ITEMS; i++) 
    {
        if(g_Cart[i][0] == INVALID_ITEM_ID) continue;

        totalWeight += g_Items[g_Cart[i][0]].itemWeight * g_Cart[i][1];
        totalValue += g_Items[g_Cart[i][0]].itemPrice * g_Cart[i][1];

        if(totalWeight > 0) 
        {
            if(totalWeight > HEAVY_ITEM_WEIGHT) 
            {
                shippingValueSouth = SHIPPING_HEAVY_SOUTH;
                shippingValueSoutheast = SHIPPING_HEAVY_SOUTHEAST;
                shippingValueNorth = SHIPPING_HEAVY_NORTH;
                shippingValueNortheast = SHIPPING_HEAVY_NORTHEAST;
            } 
            else 
            {
                shippingValueSouth = SHIPPING_DEFAULT_SOUTH;
                shippingValueSoutheast = SHIPPING_DEFAULT_SOUTHEAST;
                shippingValueNorth = SHIPPING_DEFAULT_NORTH;
                shippingValueNortheast = SHIPPING_DEFAULT_NORTHEAST;
            }
        }
    }

    printf("\n==================== FRETE ====================\n");
    printf("Valor total dos produtos: R$ %0.2f\n", totalValue);
    printf("Peso total dos produtos: %0.2fKg\n", totalWeight / 1000);

    if(totalWeight > 0) 
    {
        printf("Valor do frete para o Sul: R$ %0.2f\n", shippingValueSouth);
        printf("Valor do frete para o Sudeste: R$ %0.2f\n", shippingValueSoutheast);
        printf("Valor do frete para o Norte: R$ %0.2f\n", shippingValueNorth);
        printf("Valor do frete para o Nordeste: R$ %0.2f\n", shippingValueNortheast);
    } 
    else 
    {
        printf("Nenhum item no carrinho, frete não será cobrado.\n");
    }

    printf("\n==================== RESUMO DA COMPRA ====================\n");
    for(i = 0; i < MAX_ITEMS; i++)
    {
        if(g_Cart[i][0] != INVALID_ITEM_ID)
        {
            printf("Código do produto: %d\n", g_Cart[i][0]);
            printf("Nome do produto: %s\n", g_Items[g_Cart[i][0]].itemName);
            printf("Peso do produto: %.2fg\n", g_Items[g_Cart[i][0]].itemWeight);
            printf("Preço do produto: R$ %.2f\n", g_Items[g_Cart[i][0]].itemPrice);
        }
    }
    
    printf("Escolha a região de entrega ([1] Região Sul; [2] Região Sudeste; [3] Região Norte; [4] Região Nordeste): ");
    ScanPrompt(inputtext);
    region = atoi(inputtext);

    float shippingValue = 0.0f;
    switch(region)
    {
        case 1:
            shippingValue = shippingValueSouth;
            printf("Região de entrega: Sul\n");
            break;
        case 2:
            shippingValue = shippingValueSoutheast;
            printf("Região de entrega: Sudeste\n");
            break;
        case 3:
            shippingValue = shippingValueNorth;
            printf("Região de entrega: Norte\n");
            break;
        case 4:
            shippingValue = shippingValueNortheast;
            printf("Região de entrega: Nordeste\n");
            break;
        default:
            printf("Região inválida!\n");
            return;
    }

    printf("Preço do frete: R$ %.2f\n", shippingValue);
    printf("Preço total da compra: R$ %.2f\n", totalValue + shippingValue);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char currentDate[32];
    strftime(currentDate, sizeof(currentDate)-1, "%d/%m/%Y %H:%M:%S", t);
    printf("Data e hora da compra: %s\n", currentDate);

    t->tm_mday += 7;
    mktime(t);
    char deliveryDate[32];
    strftime(deliveryDate, sizeof(deliveryDate)-1, "%d/%m/%Y", t);
    printf("Data prevista de entrega: %s\n", deliveryDate);

    printf("=========================================================\n");
    WAIT_FOR_INPUT();
}
