#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    void **pointers = NULL; // Inicializa o ponteiro
    size_t count = 0;      // Contador para o n�mero de ponteiros
    void *ptr;

    // Loop para alocar 1GB (1024MB)
    while (true) { // Ajusta a condi��o para alocar at� 1024 MB
        ptr = malloc(1024 * 1024); // Aloca 1MB
        if (ptr == NULL) {
            printf("Erro ao alocar mem�ria.\n");
            break; // Sai do loop se a aloca��o falhar
        }

        // Realoca o array de ponteiros para incluir o novo ponteiro
        void **temp = (void **)realloc(pointers, (count + 1) * sizeof(void*)); // Cast para void**
        if (temp == NULL) {
            printf("Erro ao realocar mem�ria.\n");
            free(ptr); // Libera o ponteiro se a realoca��o falhar
            break;
        }
        pointers = temp; // Atualiza pointers se a realoca��o for bem-sucedida
        pointers[count++] = ptr; // Armazena o ponteiro no array
    }

    printf("Mem�ria alocada: %zu MB\n", count); // Exibe a quantidade de mem�ria alocada

    sleep(10);

    // Libera a mem�ria alocada
    for (size_t i = 0; i < count; i++) {
        free(pointers[i]); // Libera cada ponteiro
    }
    free(pointers); // Libera o array de ponteiros

    return 0;
}
