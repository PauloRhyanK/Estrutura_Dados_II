#include <stdio.h>
#include <stdlib.h>

/**
Paulo Rhyan Kuster - CC6N

Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
• Escreva funções que recebam um ponteiro para a raiz da árvore AVL e façam:
• Função de balanceamento;
• Inserção de um elemento na árvore;
• Pesquisa de um elemento na árvore;
• Exclusão de um elemento na árvore

 **/

// Estrutura do nó da árvore AVL
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Função para obter a altura de um nó
int height(Node* N) {
    if (N == NULL){
        return 0;
    }
    return N->height;
}

// Função para obter o valor máximo de dois inteiros
int max(int a, int b) {
    if( a > b ){
        return a;
    }   else
    {
        return b;
    }
}

// Função para criar um novo nó
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Novo nó é adicionado inicialmente como folha
    return node;
}

// Rotação à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna a nova raiz
    return x;
}

// Rotação à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna a nova raiz
    return y;
}

// Obtém o fator de balanceamento de um nó
int getBalance(Node* N) {
    if (N == NULL){
        return 0;
    }
    return height(N->left) - height(N->right);
}

// Função para inserir um elemento na árvore AVL
Node* insert(Node* node, int data) {

    // Passo 1: Inserir normalmente 
    if (node == NULL){
        return newNode(data);
    }

    if (data < node->data){
        node->left = insert(node->left, data);
    }

    else if (data > node->data){
        node->right = insert(node->right, data);
    }

    else{
        return node; // Pra não ter valor duplicado
    }

    // Passo 2: Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Passo 3: Obter o fator de balanceamento do nó ancestral
    int balance = getBalance(node);

    // Se o nó estiver desbalanceado, 4 casos são tratados:

    // Caso Esquerda-Esquerda
    if (balance > 1 && data < node->left->data){
        return rightRotate(node);
    }

    // Caso Direita-Direita
    if (balance < -1 && data > node->right->data){
        return leftRotate(node);
    }

    // Caso Esquerda-Direita
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retorna o nó (inalterado) ponteiro
    return node;
}

// Função para encontrar o nó com o menor valor
Node* minValueNode(Node* node) {
    Node* current = node;

    // Encontra a folha mais à esquerda
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Função para excluir um elemento da árvore AVL
Node* deleteNode(Node* root, int data) {
    // Passo 1: Excluir normalmente da BST
    if (root == NULL){
        return root;
    }

    if (data < root->data){
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data){
        root->right = deleteNode(root->right, data);
    }
    else {
        // Nó encontrado, agora precisamos removê-lo

        // Nó com apenas um filho ou sem filhos
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // Caso sem filhos
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // Caso com um único filho
                *root = *temp;
            free(temp);
        } else {
            // Nó com dois filhos: Obter o sucessor (menor nó da subárvore à direita)
            Node* temp = minValueNode(root->right);

            // Copiar o valor do sucessor
            root->data = temp->data;

            // Excluir o sucessor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // Se a árvore tinha apenas um nó, retorne
    if (root == NULL){
        return root;
    }

    // Passo 2: Atualizar a altura do nó atual
    root->height = max(height(root->left), height(root->right)) + 1;

    // Passo 3: Obter o fator de balanceamento do nó
    int balance = getBalance(root);

    // Se o nó estiver desbalanceado, 4 casos são tratados:

    // Caso Esquerda-Esquerda
    if (balance > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }

    // Caso Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso Direita-Direita
    if (balance < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função para pesquisar um elemento na árvore AVL
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data){
        return root;
    }

    if (data < root->data){
        return search(root->left, data);
    }

    return search(root->right, data);
}

// Função para imprimir a árvore AVL em ordem
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Função para imprimir a árvore AVL
void printTree(Node* root, int space) {
    // Quantidade de espaços entre níveis
    const int COUNT = 10;
    if (root == NULL) {
        return;
    }

    // Aumenta o espaço entre os níveis
    space += COUNT;

    // Imprime o filho direito primeiro
    printTree(root->right, space);

    // Imprime o nó atual
    printf("\n");
    for (int i = COUNT; i < space; i++){
        printf(" ");
    }
    printf("%d\n", root->data);

    // Imprime o filho esquerdo
    printTree(root->left, space);
}


int main()
{
    Node* root = NULL;

    // Inserindo elementos na árvore AVL
    root = insert(root, 30);
    root = insert(root, 24);
    root = insert(root, 20);
    root = insert(root, 35);
    root = insert(root, 27);
    root = insert(root, 33);
    root = insert(root, 38);
    root = insert(root, 25);
    root = insert(root, 22);
    root = insert(root, 34);
    root = insert(root, 40);
    root = insert(root, 29);
    printTree(root, 3);

    printf("\nLetra A - Inserir 31 ---------------------------\n");
    root = insert(root, 31);
    printTree(root, 3);

    printf("\nLetra B - Inserir 15 ---------------------------\n");
    root = insert(root, 15);
    printTree(root, 3);

    printf("\nLetra C - Inserir 23 ----------------------------\n");
    root = insert(root, 23);
    printTree(root, 3);

    printf("\nLetra D - Excluir 24 ---------------------------\n");
    root = deleteNode(root, 24);
    printTree(root, 3);

    printf("\nLetra E - Excluir 35 ---------------------------\n");
    root = deleteNode(root, 35);
    printTree(root, 3);

    printf("\nLetra F - Inserir 24 ---------------------------\n");
    root = insert(root, 24);
    printTree(root, 3);

    printf("\nLetra G - Excluir 27 ---------------------------\n");
    root = deleteNode(root, 27);
    printTree(root, 3);

    printf("\nLetra H - Inserir 32 ---------------------------\n");
    root = insert(root, 32);
    printTree(root, 3);

    printf("\nLetra I - Excluir 30 ---------------------------\n");
    root = deleteNode(root, 30);
    printTree(root, 3);

    printf("\nLetra J - Inserir 21 ---------------------------\n");
    root = insert(root, 21);
    printTree(root, 3);

    return 0;
}
