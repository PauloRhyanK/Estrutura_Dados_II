#include <stdio.h>
#include <stdlib.h>

void mergeFiles(const char *file1, const char *file2, const char *outputFile) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(outputFile, "w");

    if (!f1 || !f2 || !out) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    int num1, num2;
    int hasNum1 = fscanf(f1, "%d", &num1);
    int hasNum2 = fscanf(f2, "%d", &num2);

    while (hasNum1 != EOF && hasNum2 != EOF) {
        if (num1 < num2) {
            fprintf(out, "%d ", num1);
            hasNum1 = fscanf(f1, "%d", &num1);
        } else {
            fprintf(out, "%d ", num2);
            hasNum2 = fscanf(f2, "%d", &num2);
        }
    }

    while (hasNum1 != EOF) {
        fprintf(out, "%d ", num1);
        hasNum1 = fscanf(f1, "%d", &num1);
    }
    while (hasNum2 != EOF) {
        fprintf(out, "%d ", num2);
        hasNum2 = fscanf(f2, "%d", &num2);
    }

    fclose(f1);
    fclose(f2);
    fclose(out);
}

int main() {
    mergeFiles("run1.txt", "run2.txt", "sorted_output.txt");
    printf("Intercalação concluída!\n");
    return 0;
}
