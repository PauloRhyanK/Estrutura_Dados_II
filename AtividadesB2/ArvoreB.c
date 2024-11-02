#include <stdio.h>
#include <stdlib.h>

#define T 3 // Grau mínimo da árvore B

typedef struct BTreeNode {
    int *keys; // Array de chaves
    int t; // Grau mínimo
    struct BTreeNode **C; // Array de ponteiros para filhos
    int n; // Número atual de chaves
    int leaf; // Verdadeiro se o nó é folha
} BTreeNode;

// Função para criar um novo nó da árvore B
BTreeNode* createNode(int t, int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc((2*t-1) * sizeof(int));
    newNode->C = (BTreeNode**)malloc(2*t * sizeof(BTreeNode*));
    newNode->n = 0;
    return newNode;
}

// Função para percorrer a árvore
void traverse(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) {
            traverse(root->C[i]);
        }
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf) {
        traverse(root->C[i]);
    }
}

// Função para buscar uma chave na árvore
BTreeNode* search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) {
        i++;
    }
    if (root->keys[i] == k) {
        return root;
    }
    if (root->leaf) {
        return NULL;
    }
    return search(root->C[i], k);
}

// Função para inserir uma nova chave na árvore
void insert(BTreeNode** root, int k) {
    BTreeNode* r = *root;
    if (r->n == 2*T-1) {
        BTreeNode* s = createNode(r->t, 0);
        *root = s;
        s->C[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Função para inserir uma chave em um nó não cheio
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > k) {
            i--;
        }
        if (x->C[i+1]->n == 2*T-1) {
            splitChild(x, i+1, x->C[i+1]);
            if (x->keys[i+1] < k) {
                i++;
            }
        }
        insertNonFull(x->C[i+1], k);
    }
}

// Função para dividir um nó filho cheio
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->t, y->leaf);
    z->n = T - 1;
    for (int j = 0; j < T-1; j++) {
        z->keys[j] = y->keys[j+T];
    }
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->C[j] = y->C[j+T];
        }
    }
    y->n = T - 1;
    for (int j = x->n; j >= i+1; j--) {
        x->C[j+1] = x->C[j];
    }
    x->C[i+1] = z;
    for (int j = x->n-1; j >= i; j--) {
        x->keys[j+1] = x->keys[j];
    }
    x->keys[i] = y->keys[T-1];
    x->n++;
}

int main() {
    BTreeNode* root = createNode(T, 1);
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("Traversal of the constructed tree is:\n");
    traverse(root);

    int k = 6;
    (search(root, k) != NULL) ? printf("\nPresent") : printf("\nNot Present");

    k = 15;
    (search(root, k) != NULL) ? printf("\nPresent") : printf("\nNot Present");

    return 0;
}