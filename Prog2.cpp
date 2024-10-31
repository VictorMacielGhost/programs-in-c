#include <stdio.h>

int main(void)
{
	char nome[30];
	int ano_nasc, idade;
	
	printf("Digite seu nome: ");
	scanf("%s", nome);
	printf("\n");
	printf("Digite o ano de nascimento: ");
	scanf("%d", &ano_nasc);
	printf("\n");
	idade = 2030 - ano_nasc;
	printf("%s vai ter %d anos de idade em 2030.", nome, idade);
	getchar();
	getchar();
	return 0;
}
