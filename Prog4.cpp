#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14

int main(void)
{
    float raio, area;

    system("cls");
    printf("Entre com o valor do Raio: ");
    scanf("%f", &raio);

    area = PI * pow(raio, 2);

    printf("a area do raio %0.2f eh de: %0.2f ", raio, area);    

    return 0;
}