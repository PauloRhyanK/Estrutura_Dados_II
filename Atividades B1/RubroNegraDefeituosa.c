#include <stdio.h>
#include <stdlib.h>

/**
Paulo Rhyan Kuster - CC6N

"A terceira atividade do diário de bordo chegou! Nesta etapa, vocês vão implementar, em Linguagem C, a estrutura de uma Árvore Red-Black."

Estrutura:
• Criação de No;
• Balanceamento;
• Inserção de um elemento na árvore;
• Exclusão de um elemento na árvore;

 **/

struct NoRb {
    int dado;
    struct NoRb *esq;
    struct NoRb *dir;
    struct NoRb *pai;
    int cor;
};
typedef struct NoRb NoRb;

// Criando No
struct NoRb *criarNo(int valor) {
    struct NoRb *novoNo = (struct NoRb *)malloc(sizeof(struct NoRb));

    novoNo->dado = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;
    novoNo->cor = 0;  // Nós são inicialmente vermelhos
    return novoNo;
}

void rotacaoesq(struct NoRb **root, struct NoRb *a) {
    struct NoRb *b = a->dir;

    // Passando filho do B, para o A
    a->dir = b->esq;
    if (b->esq != NULL) { // Corrigido para verificar se b->esq não é NULL
        b->esq->pai = a;
    }

    // Passando Pai do A para o B
    b->pai = a->pai;

    // Verificando se o B era um filho dir ou esq, para alterar o NO pai adequadamente ou setar a nova RAIZ
    if (a->pai == NULL) {
        *root = b;
    } else if (a == a->pai->esq) {
        a->pai->esq = b;
    } else {
        a->pai->dir = b;
    }

    // Finalizando a rotação
    b->esq = a;
    a->pai = b;
}

void rotacaodir(struct NoRb **root, struct NoRb *a) {
    struct NoRb *b = a->esq;

    // Passando filho do B, para o A
    a->esq = b->dir;
    if (b->dir != NULL) {
        b->dir->pai = a;
    }

    // Passando Pai do A para o B
    a->pai = b->pai;

    // Verificando se o B era um filho dir ou esq, para alterar o NO pai adequadamente ou setar a nova RAIZ
    if (a->pai == NULL) {
        *root = b;
    } else if (a == a->pai->dir) {
        a->pai->dir = b;
    } else {
        a->pai->esq = b;
    }

    // Finalizando a rotação
    b->dir = a;

    // Alterando Pai
    a->pai = b;
}

void balancear(struct NoRb **raiz, struct NoRb *node) {
    while (node != *raiz && node->pai != NULL && node->pai->cor == 0) {
        // Verificando se o no pai e o filho da esquerda ou direita
        if (node->pai == node->pai->pai->esq) {
            struct NoRb *x = node->pai->pai->dir;

            // Verificando se o No avo tem um filho direito
            if (x != NULL && x->cor == 0) {
                x->cor = 1;
                node->pai->pai->cor = 0;
                node->pai->cor = 1;

                node = node->pai->pai;
            } else {
                if (node == node->pai->dir) {
                    node = node->pai;
                    rotacaoesq(raiz, node);
                }
                node->pai->cor = 1;
                node->pai->pai->cor = 0;
                rotacaodir(raiz, node->pai->pai);
            }
        } else {
            // Verificando se o No avo tem um filho esquerdo
            struct NoRb *x = node->pai->pai->esq;
            if (x != NULL && x->cor == 0) {
                x->cor = 1;
                node->pai->pai->cor = 0;
                node->pai->cor = 1;

                node = x;
            } else {
                if (node == node->pai->esq) {
                    node = node->pai;
                    rotacaodir(raiz, node);
                }
                node->pai->cor = 1;
                node->pai->pai->cor = 0;
                rotacaoesq(raiz, node->pai->pai);
            }
        }
    }
    (*raiz)->cor = 1;
}

void inserirNo(struct NoRb **root, int valor) {
    struct NoRb *novoNo = criarNo(valor); // cria um novo No com o valor inserido
    struct NoRb *paiX = NULL; // Valor para armazenar o pai
    struct NoRb *x = *root; // Variavel para percorrer arvore

    while (x != NULL) {
        paiX = x; //  Armazena o pai do No atual

        // Percorrendo arvore até achar o lugar certo para o novo No
        if (novoNo->dado < x->dado) {
            x = x->esq;
        } else if (novoNo->dado > x->dado) {
            x = x->dir;
        } else {
            free(novoNo);
            return;
        }
    }
    //  Insere o novo pai do No
    novoNo->pai = paiX;

    // Inserindo Novo No
    if (paiX == NULL) {
        *root = novoNo;
    } else if (novoNo->dado < paiX->dado) {
        paiX->esq = novoNo;
    } else {
        paiX->dir = novoNo;
    }

    // Balanceando Arvore
    balancear(root, novoNo);
}

// Função para imprimir a árvore em ordem (simples)
void emOrdem(struct NoRb *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d (%s) ", raiz->dado, raiz->cor == 0 ? "RED" : "BLK");
        emOrdem(raiz->dir);
    }
}

// Função para imprimir a árvore no formato hierárquico
void imprimeArvoreRB(struct NoRb *raiz, int espacos) {
    if (raiz != NULL) {
        imprimeArvoreRB(raiz->dir, espacos + 4);

        for (int i = 0; i < espacos; i++)
            printf(" ");
        printf("%d (%s)\n", raiz->dado, raiz->cor == 0 ? "RED" : "BLK");

        imprimeArvoreRB(raiz->esq, espacos + 4);
    }
}

// Função principal
int main() {
    struct NoRb *raiz = NULL;
    
    // Exemplo de inserção de valores na árvore Red-Black
    int vetor[] = {12, 31, 20, 17, 11, 8, 3, 24, 15, 33};
    int tam = sizeof(vetor) / sizeof(vetor[0]);

    for (int i = 0; i < tam; i++) {
        inserirNo(&raiz, vetor[i]);
    }

    // Imprime a árvore Red-Black
    printf("Árvore Red-Black em formato hierárquico:\n");
    imprimeArvoreRB(raiz, 0);

    // Imprime a árvore em ordem
    printf("\nÁrvore Red-Black em ordem:\n");
    emOrdem(raiz);
    printf("\n");

    return 0;
}
