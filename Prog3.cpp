    #include <stdio.h>
    #include <stdlib.h>

    int limpa_tela(void);

    #undef gets
    #define gets(param) gets(param), limpa_tela()


    int main(void)
    {
        char nome[30], endereco[20], cidade[15], uf[2], tel[13];

        puts("Digite seu Nome: ");
        gets(nome);
        puts("Digite seu Endereco: ");
        gets(endereco);
        puts("Digite seu Cidade: ");
        gets(cidade);
        puts("Digite seu UF: ");
        gets(uf);
        puts("Digite seu Telefone: ");
        gets(tel);


        printf("%s, %s, %s, %s, %s", nome, endereco, cidade, uf, tel);
        getchar();
        return 0;
    }

    int limpa_tela(void)
    {
        #ifdef _WIN32
            return system("cls");
        #else
            return system("clear");
        #endif
    }