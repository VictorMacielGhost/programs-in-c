#include <stdio.h>

int main()
{
    float peso, altura, imc;
    printf("\nPeso: ");
    scanf("%f", &peso);
    printf("\nAltura: ");
    scanf("%f", &altura);
    imc = altura / peso;
    printf("Imc: %0.2f", imc);
    getchar();
    getchar();
    return 0;
}