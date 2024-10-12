#include <stdio.h>
#include <stdlib.h>

struct NoRb {
    int dado;                // Valor armazenado no nó
    struct NoRb *esq;       // Ponteiro para o filho à esquerda
    struct NoRb *dir;       // Ponteiro para o filho à direita
    struct NoRb *pai;       // Ponteiro para o pai
    int cor;                // Cor do nó (0 = vermelho, 1 = preto)
};

typedef struct NoRb NoRb;

// Criando Nó
struct NoRb *criarNo(int valor) {
    struct NoRb *novoNo = (struct NoRb*)malloc(sizeof(struct NoRb));
    novoNo->dado = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;
    novoNo->cor = 0;  // Nós são inicialmente vermelhos
    return novoNo;
}

// Rotação à esquerda
void rotacaoesq(struct NoRb **root, struct NoRb *a) {
    struct NoRb *b = a->dir;
    a->dir = b->esq;
    if (b->esq != NULL) {
        b->esq->pai = a;
    }
    b->pai = a->pai;
    if (a->pai == NULL) {
        *root = b;
    } else if (a == a->pai->esq) {
        a->pai->esq = b;
    } else {
        a->pai->dir = b;
    }
    b->esq = a;
    a->pai = b;
}

// Rotação à direita
void rotacaodir(struct NoRb **root, struct NoRb *a) {
    struct NoRb *b = a->esq;
    a->esq = b->dir;
    if (b->dir != NULL) {
        b->dir->pai = a;
    }
    b->pai = a->pai;
    if (a->pai == NULL) {
        *root = b;
    } else if (a == a->pai->dir) {
        a->pai->dir = b;
    } else {
        a->pai->esq = b;
    }
    b->dir = a;
    a->pai = b;
}

// Função para balancear a árvore
void balancear(struct NoRb **raiz, struct NoRb *node) {
    while (node != *raiz && node->pai != NULL && node->pai->cor == 0) {
        if (node->pai == node->pai->pai->esq) {
            struct NoRb *x = node->pai->pai->dir;
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
            struct NoRb *x = node->pai->pai->esq;
            if (x != NULL && x->cor == 0) {
                x->cor = 1;
                node->pai->pai->cor = 0;
                node->pai->cor = 1;
                node = node->pai->pai;
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

// Função para substituir um nó por outro
void substituirNo(struct NoRb **raiz, struct NoRb *u, struct NoRb *v) {
    if (u->pai == NULL) {
        *raiz = v;
    } else if (u == u->pai->esq) {
        u->pai->esq = v;
    } else {
        u->pai->dir = v;
    }
    if (v != NULL) {
        v->pai = u->pai;
    }
}

// Função auxiliar para encontrar o nó mínimo
struct NoRb *minimo(struct NoRb *node) {
    while (node->esq != NULL) {
        node = node->esq;
    }
    return node;
}

// Função para balancear após a exclusão
void balancearExclusao(struct NoRb **raiz, struct NoRb *x) {
    while (x != *raiz && x->cor == 1) {
        if (x == x->pai->esq) {
            struct NoRb *w = x->pai->dir;
            if (w->cor == 0) {
                w->cor = 1;
                x->pai->cor = 0;
                rotacaoesq(raiz, x->pai);
                w = x->pai->dir;
            }
            if ((w->esq == NULL || w->esq->cor == 1) && 
                (w->dir == NULL || w->dir->cor == 1)) {
                w->cor = 0;
                x = x->pai;
            } else {
                if (w->dir == NULL || w->dir->cor == 1) {
                    w->esq->cor = 1;
                    w->cor = 0;
                    rotacaodir(raiz, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 1;
                if (w->dir != NULL) w->dir->cor = 1;
                rotacaoesq(raiz, x->pai);
                x = *raiz;
            }
        } else {
            struct NoRb *w = x->pai->esq;
            if (w->cor == 0) {
                w->cor = 1;
                x->pai->cor = 0;
                rotacaodir(raiz, x->pai);
                w = x->pai->esq;
            }
            if ((w->dir == NULL || w->dir->cor == 1) && 
                (w->esq == NULL || w->esq->cor == 1)) {
                w->cor = 0;
                x = x->pai;
            } else {
                if (w->esq == NULL || w->esq->cor == 1) {
                    w->dir->cor = 1;
                    w->cor = 0;
                    rotacaoesq(raiz, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 1;
                if (w->esq != NULL) w->esq->cor = 1;
                rotacaodir(raiz, x->pai);
                x = *raiz;
            }
        }
    }
    x->cor = 1;
}

// Função para excluir um nó da árvore
void excluirNo(struct NoRb **raiz, struct NoRb *z) {
    struct NoRb *y = z;
    int yCorOriginal = y->cor;
    struct NoRb *x;

    if (z->esq == NULL) {
        x = z->dir;
        substituirNo(raiz, z, z->dir);
    } else if (z->dir == NULL) {
        x = z->esq;
        substituirNo(raiz, z, z->esq);
    } else {
        y = minimo(z->dir);
        yCorOriginal = y->cor;
        x = y->dir;
        if (y->pai == z) {
            if (x != NULL) x->pai = y;
        } else {
            substituirNo(raiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        substituirNo(raiz, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    free(z);
    if (yCorOriginal == 1 && x != NULL) {
        balancearExclusao(raiz, x);
    }
}

// Função para buscar um nó pelo valor
struct NoRb *buscarNo(struct NoRb *raiz, int valor) {
    while (raiz != NULL && valor != raiz->dado) {
        if (valor < raiz->dado) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return raiz;
}

// Função para inserir um novo nó
void inserirNo(struct NoRb **root, int valor) {
    struct NoRb *novoNo = criarNo(valor); 
    struct NoRb *paiX = NULL;
    struct NoRb *x = *root;

    while (x != NULL) {
        paiX = x;
        if (novoNo->dado < x->dado) {
            x = x->esq;
        } else if (novoNo->dado > x->dado) {
            x = x->dir;
        } else {
            free(novoNo); 
            return;
        }
    }

    novoNo->pai = paiX;
    if (paiX == NULL) {
        *root = novoNo;
    } else if (novoNo->dado < paiX->dado) {
        paiX->esq = novoNo;
    } else {
        paiX->dir = novoNo;
    }
    balancear(root, novoNo);
}

// Função para imprimir a árvore em ordem
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

    // Excluir um nó
    struct NoRb *noExcluir = buscarNo(raiz, 20);
    if (noExcluir != NULL) {
        excluirNo(&raiz, noExcluir);
        printf("\nÁrvore Red-Black após exclusão do nó 20:\n");
        imprimeArvoreRB(raiz, 0);
        printf("\nÁrvore Red-Black em ordem:\n");
        emOrdem(raiz);
        printf("\n");
    } else {
        printf("Nó não encontrado para exclusão.\n");
    }

    return 0;
}