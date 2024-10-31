#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    void **pointers = NULL; // Inicializa o ponteiro
    size_t count = 0;      // Contador para o número de ponteiros
    void *ptr;

    // Loop para alocar 1GB (1024MB)
    while (true) { // Ajusta a condição para alocar até 1024 MB
        ptr = malloc(1024 * 1024); // Aloca 1MB
        if (ptr == NULL) {
            printf("Erro ao alocar memória.\n");
            break; // Sai do loop se a alocação falhar
        }

        // Realoca o array de ponteiros para incluir o novo ponteiro
        void **temp = (void **)realloc(pointers, (count + 1) * sizeof(void*)); // Cast para void**
        if (temp == NULL) {
            printf("Erro ao realocar memória.\n");
            free(ptr); // Libera o ponteiro se a realocação falhar
            break;
        }
        pointers = temp; // Atualiza pointers se a realocação for bem-sucedida
        pointers[count++] = ptr; // Armazena o ponteiro no array
    }

    printf("Memória alocada: %zu MB\n", count); // Exibe a quantidade de memória alocada

    sleep(10);

    // Libera a memória alocada
    for (size_t i = 0; i < count; i++) {
        free(pointers[i]); // Libera cada ponteiro
    }
    free(pointers); // Libera o array de ponteiros

    return 0;
}
