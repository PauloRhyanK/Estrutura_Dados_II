#include <stdio.h>
#include <stdlib.h>

#define K 3 // Número de runs para intercalar

typedef struct
{
    int value;
    int fileIndex;
} HeapNode;

// Função para manter a propriedade do min-heap
void minHeapify(HeapNode heap[], int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;
    if (smallest != i)
    {
        HeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, size, smallest);
    }
}

// Função para construir um min-heap a partir de um array
void buildMinHeap(HeapNode heap[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        minHeapify(heap, size, i);
    }
}

// Função para realizar a intercalação k-vias
void kWayMerge(const char *files[], int k, const char *outputFile)
{
    FILE *in[k];
    FILE *out = fopen(outputFile, "w");
    HeapNode heap[k];
    int i;

    // Abrir arquivos de entrada
    for (i = 0; i < k; i++)
    {
        in[i] = fopen(files[i], "r");
        fscanf(in[i], "%d", &heap[i].value);
        heap[i].fileIndex = i;
    }

    // Construir o min-heap inicial
    buildMinHeap(heap, k);

    while (1)
    {
        // Extrair o menor elemento do heap
        HeapNode min = heap[0];
        fprintf(out, "%d ", min.value);

        // Ler o próximo elemento do mesmo arquivo
        if (fscanf(in[min.fileIndex], "%d", &heap[0].value) != 1)
        {
            // Se o arquivo estiver vazio, substituir pelo último elemento do heap
            heap[0] = heap[k - 1];
            k--;
        }

        // Reorganizar o heap
        minHeapify(heap, k, 0);

        // Se o heap estiver vazio, terminar
        if (k == 0)
            break;
    }

    // Fechar todos os arquivos
    for (i = 0; i < k; i++)
    {
        fclose(in[i]);
    }
    fclose(out);
}

int main()
{
    const char *inputFiles[K] = {"run1.txt", "run2.txt", "run3.txt"};
    kWayMerge(inputFiles, K, "sorted_output.txt");
    printf("Intercalação k-vias concluída!\n");
    return 0;
}