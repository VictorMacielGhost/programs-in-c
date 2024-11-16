#include <stdio.h>

int main() 
{
    int num1, num2, choice;
    float result;

    printf("Digite o primeiro numero: ");
    scanf("%d", &num1);
    printf("Digite o segundo numero: ");
    scanf("%d", &num2);

    printf("Escolha a operacao:\n");
    printf("1. Adicao\n");
    printf("2. Subtracao\n");
    printf("3. Multiplicacao\n");
    printf("4. Divisao\n");
    printf("Digite sua escolha (1-4): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            result = num1 + num2;
            printf("Resultado: %d + %d = %0.2f\n", num1, num2, result);
            break;
        case 2:
            result = num1 - num2;
            printf("Resultado: %d - %d = %0.2f\n", num1, num2, result);
            break;
        case 3:
            result = num1 * num2;
            printf("Resultado: %d * %d = %0.2f\n", num1, num2, result);
            break;
        case 4:
            if(num2 != 0) 
            {
                result = (float)num1 / num2;
                printf("Resultado: %d / %d = %0.2f\n", num1, num2, result);
            } 
            else 
            {
                printf("Erro: Divisao por zero nao eh permitida.\n");
            }
            break;
        default:
            printf("Escolha invalida.\n");
            break;
    }

    return 0;
}