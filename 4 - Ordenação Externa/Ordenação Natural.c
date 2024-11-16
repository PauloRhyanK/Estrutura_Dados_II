#include <stdio.h>
#include <stdlib.h>

void findNaturalRuns(const char *inputFile, const char *runFiles[], int *numRuns) {
    FILE *in = fopen(inputFile, "r");
    if (!in) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    int current, previous;
    int runIndex = 0;

    FILE *out = fopen(runFiles[runIndex], "w");

    fscanf(in, "%d", &previous);
    fprintf(out, "%d ", previous);

    while (fscanf(in, "%d", &current) != EOF) {
        if (current < previous) {
            fclose(out);
            runIndex++;
            out = fopen(runFiles[runIndex], "w");
        }
        fprintf(out, "%d ", current);
        previous = current;
    }
    fclose(out);
    fclose(in);

    *numRuns = runIndex + 1;
}

void mergeRuns(const char *runFiles[], int numRuns, const char *outputFile) {
    FILE *out = fopen(outputFile, "w");
    FILE *in[numRuns];
    for (int i = 0; i < numRuns; i++) {
        in[i] = fopen(runFiles[i], "r");
        if (!in[i]) {
            printf("Erro ao abrir run %d\n", i);
            return;
        }
    }

    int values[numRuns];
    for (int i = 0; i < numRuns; i++) {
        fscanf(in[i], "%d", &values[i]);
    }

    int minIndex;
    while (1) {
        minIndex = -1;
        for (int i = 0; i < numRuns; i++) {
            if (in[i] && (minIndex == -1 || values[i] < values[minIndex])) {
                minIndex = i;
            }
        }
        if (minIndex == -1) break;

        fprintf(out, "%d ", values[minIndex]);
        if (fscanf(in[minIndex], "%d", &values[minIndex]) == EOF) {
            fclose(in[minIndex]);
            in[minIndex] = NULL;
        }
    }

    fclose(out);
}

int main() {
    const char *runFiles[100] = {"run0.txt", "run1.txt", "run2.txt"};
    int numRuns;
    findNaturalRuns("input.txt", runFiles, &numRuns);
    mergeRuns(runFiles, numRuns, "sorted_output.txt");
    printf("Ordenação natural concluída!\n");
    return 0;
}
