#include <stdio.h>
#include <stdlib.h>

#define K 3 // Número de runs para intercalar

typedef struct {
    int value;
    int fileIndex;
} HeapNode;

void minHeapify(HeapNode heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;
    if (smallest != i) {
        HeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, size, smallest);
    }
}

void buildMinHeap(HeapNode heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        minHeapify(heap, size, i);
    }
}

void kWayMerge(const char *files[], int k, const char *outputFile) {
    FILE *in[k];
    for (int i = 0; i < k; i++) {
        in[i] = fopen(files[i], "r");
        if (!in[i]) {
            printf("Erro ao abrir o arquivo %s\n", files[i]);
            return;
        }
    }

    FILE *out = fopen(outputFile, "w");
    if (!out) {
        printf("Erro ao abrir o arquivo de saída!\n");
        return;
    }

    HeapNode heap[K];
    int heapSize = 0;

    for (int i = 0; i < k; i++) {
        if (fscanf(in[i], "%d", &heap[heapSize].value) != EOF) {
            heap[heapSize].fileIndex = i;
            heapSize++;
        }
    }

    buildMinHeap(heap, heapSize);

    while (heapSize > 0) {
        fprintf(out, "%d ", heap[0].value);
        if (fscanf(in[heap[0].fileIndex], "%d", &heap[0].value) == EOF) {
            heap[0] = heap[--heapSize];
        }
        minHeapify(heap, heapSize, 0);
    }

    for (int i = 0; i < k; i++) {
        fclose(in[i]);
    }
    fclose(out);
}

int main() {
    const char *inputFiles[K] = {"run1.txt", "run2.txt", "run3.txt"};
    kWayMerge(inputFiles, K, "sorted_output.txt");
    printf("Intercalação k-vias concluída!\n");
    return 0;
}
