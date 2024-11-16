#include <stdio.h>
#include <stdlib.h>

void createRuns(const char *inputFile, int runSize, int numRuns) {
    FILE *in = fopen(inputFile, "r");
    if (!in) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    int *buffer = (int *)malloc(runSize * sizeof(int));

    for (int runIndex = 0; runIndex < numRuns; runIndex++) {
        char runFileName[20];
        sprintf(runFileName, "run%d.txt", runIndex);

        int count = 0;
        while (count < runSize && fscanf(in, "%d", &buffer[count]) != EOF) {
            count++;
        }

        qsort(buffer, count, sizeof(int), compare);  // Ordena o bloco na memória

        FILE *out = fopen(runFileName, "w");
        for (int i = 0; i < count; i++) {
            fprintf(out, "%d ", buffer[i]);
        }

        fclose(out);
    }

    fclose(in);
    free(buffer);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    const char *inputFile = "data.txt";
    int runSize = 100000;  // Exemplo: cada "run" terá 100.000 elementos
    int numRuns = 10;      // Número total de runs

    createRuns(inputFile, runSize, numRuns);
    printf("Divisão e criação de runs concluídas!\n");
    return 0;
}
