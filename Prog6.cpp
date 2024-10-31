#include <stdio.h>

#define PI 3.1415

int main()
{
    float raio, area;
    puts("Digite o valor do raio");
    scanf("%f", &raio);
    area = PI * (raio * raio);
    printf("\nO valor da area eh de: %0.2f", area);
    getchar();
    getchar();
    return 0;
}