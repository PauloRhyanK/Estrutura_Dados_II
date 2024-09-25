#include <stdio.h>
#include <stdlib.h>

/**
Paulo Rhyan Kuster - CC6N

"A terceira atividade do diário de bordo chegou! Nesta etapa, vocês vão implementar, em Linguagem C,a estrutura de uma Árvore Red-Black."

Estrutura:
• Criação de No;
• Balanceamento;
• Inserção de um elemento na árvore;
• Exclusão de um elemento na árvore;

 **/


struct NoRb{
    int dado;
    struct NoRb *esq;
    struct NoRb *dir;
    struct NoRb *pai;
    int cor;
};


// Criando No
struct NoRb *criarNo(int valor){
    struct NoRb *novoNo = (struct NoRb*)malloc(sizeof(struct NoRb));

    novoNo->dado = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    novoNo->cor = 0;

    return novoNo;
}



void rotacaoesq(struct NoRb **root, struct NoRb* A){
    struct NoRb *B = A->dir;



    B->esq = A;

    return B;
}

void rotacaodir(struct NoRb **root, struct NoRb* A){
    struct NoRb *B = A->esq;

    // Passando filho do B, para o A
    A->esq = B->dir;
    if (B->dir != NULL){
        B->dir->pai = A;
    }

    // Passando Pai do A para o B
    A->pai = B->pai;

    // Verificando se o B era um filho dir ou esq, para alterar o NO pai adequadamente ou setar a nova RAIZ
    if(A->pai == NULL){
        *root = B;
    }else if ( A == A->pai->dir){
        A->pai->dir = B;
    }else {
        A->pai->esq = B;
    }

    // Finalizando a rotação
    B->dir = A;

    // Alterando Pai
    A->pai = B;
}


struct NoRb *balancear(struct NoRb* tree){
    if (tree == NULL){
        return 1;
    }

    int countesq = 0;
    int countdir = 0;

    // Percorrendo esquerda

}










struct NoRb *inserirNo(struct NoRb* root, int valor){

    struct NoRb *NovoNo =  criarNo(valor);

    if (root == NULL){
        root = NovoNo;
        
        return root;
    }
    else 
    {
        if (valor >  root->dado){
            inserirNo(root->dir, valor);
        }
        else if (valor < root->dado){
            inserirNo(root->esq, valor);
        }else{
            return root;
        }
    }
};




