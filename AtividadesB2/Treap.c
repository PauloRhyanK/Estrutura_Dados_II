#include <stdio.h>
#include <stdlib.h>

// Definição do nó da Treap
typedef struct Treap {
    struct Treap* left;
    struct Treap* right;
    int value;
    int priority;
} Treap;

// Função para criar um novo nó
Treap* newNode(int value, int priority) {
    Treap* node = (Treap*)malloc(sizeof(Treap));
    if (node == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->priority = priority;
    return node;
}

// Rotação à direita
Treap* rotRight(Treap* node) {
    Treap* B = node->left;
    node->left = B->right;
    B->right = node;
    return B;
}

// Rotação à esquerda
Treap* rotLeft(Treap* node) {
    Treap* B = node->right;
    node->right = B->left;
    B->left = node;
    return B;
}

// Inserção de um novo nó
Treap* insert(int value, int priority, Treap* node) {
    if (node == NULL) {
        return newNode(value, priority);
    }
    if (value < node->value) {
        node->left = insert(value, priority, node->left);
        if (node->left != NULL && node->left->priority > node->priority) {
            node = rotRight(node);
        }
    } else if (value > node->value) {
        node->right = insert(value, priority, node->right);
        if (node->right != NULL && node->right->priority > node->priority) {
            node = rotLeft(node);
        }
    }
    return node;
}

// Remoção de um nó
Treap* delete(int value, Treap* node) {
    if (node == NULL) {
        return NULL;
    }
    if (value < node->value) {
        node->left = delete(value, node->left);
    } else if (value > node->value) {
        node->right = delete(value, node->right);
    } else {
        if (node->left == NULL || node->right == NULL) {
            Treap* temp = (node->left != NULL) ? node->left : node->right;
            free(node);
            return temp;
        } else {
            if (node->left->priority > node->right->priority) {
                node = rotRight(node);
                node->right = delete(value, node->right);
            } else {
                node = rotLeft(node);
                node->left = delete(value, node->left);
            }
        }
    }
    return node;
}

// Impressão da Treap em ordem
void inOrderP(Treap* root) {
    if (root != NULL) {
        inOrderP(root->left);
        printf("Valor: %d, Prioridade: %d\n", root->value, root->priority);
        inOrderP(root->right);
    }
}

// Impressão hierárquica da Treap
void printTree(Treap* root, int space) {
    const int COUNT = 10;
    if (root == NULL) return;

    space += COUNT;
    printTree(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", root->value);

    printTree(root->left, space);
}

// Função para liberar a memória da Treap
void freeTreap(Treap* root) {
    if (root != NULL) {
        freeTreap(root->left);
        freeTreap(root->right);
        free(root);
    }
}

// Função para manipular a Treap
void select(Treap** root) {
    int opcao;
    do {
        printf("\n1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Imprimir\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        int valor, prioridade;
        switch (opcao) {
            case 1:
                printf("Digite o valor e a prioridade: ");
                scanf("%d %d", &valor, &prioridade);
                *root = insert(valor, prioridade, *root);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                *root = delete(valor, *root);
                break;
            case 3:
                printTree(*root, 3);
                printf("Árvore em ordem:\n");
                inOrderP(*root);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}

// Função principal
int main() {
    Treap* root = NULL;
    select(&root);
    freeTreap(root);  // Libera a memória alocada
    return 0;
}
