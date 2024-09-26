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



void rotacaoesq(struct NoRb **root, struct NoRb *a){
    struct NoRb *b = a->dir;

    // Passando filho do B, para o A
    a->dir = b->esq;
    if (a->esq != NULL){
        a->dir->pai = a;
    }

    //Passando Pai do A para o B
    a->pai =b->pai;

    // Verificando se o B era um filho dir ou esq, para alterar o NO pai adequadamente ou setar a nova RAIZ
    if (a->pai == NULL){
        *root = b;
    }
    else if(a == a->pai->dir){
        a->pai->dir = b;
    }else {
        a->pai->esq = b;
    }

     // Finalizando a rotação
    b->esq = a;

    a->pai = b;
}

void rotacaodir(struct NoRb **root, struct NoRb *a){
    struct NoRb *b = a->esq;

    // Passando filho do B, para o A
    a->esq = b->dir;
    if (b->dir != NULL){
        b->dir->pai = a;
    }

    // Passando Pai do A para o B
    a->pai = b->pai;

    // Verificando se o B era um filho dir ou esq, para alterar o NO pai adequadamente ou setar a nova RAIZ
    if(a->pai == NULL){
        *root = b;
    }else if ( a == a->pai->dir){
        a->pai->dir = b;
    }else {
        a->pai->esq = b;
    }

    // Finalizando a rotação
    b->dir = a;

    // Alterando Pai
    a->pai = b;
}


void balancear(struct NoRb **raiz,  struct NoRb *node){

    while( node != *raiz && node->pai->cor == 0 )
    {
        // Verificando se o no pai e o filho da esquerda ou direita
        if( node->pai == node->pai->pai->esq){
    
            struct NoRb *x = node->pai->pai;

            //Verificando se o No avo tem um filho direito
            if (x->dir != NULL && x->dir->cor == 0){
                node->pai->pai->dir->cor = 1;
                node->pai->pai->cor = 0;
                node->pai->cor =1;

                node =  x;

            }else{
                
                if (node == node->pai->dir){
                    node = node->pai;
                    rotacaoesq(raiz, node);
                }
                node->pai->cor= 0;
                node->pai->pai->cor = 1;
                rotacaodir(raiz, node);
            }
        }
        else
        {   
             //Verificando se o No avo tem um filho esquerdo
            struct NoRb *x = node->pai->pai;
            if (x->esq != NULL && x->esq->cor == 0){
                node->pai->pai->esq->cor = 1;
                node->pai->pai->cor = 0;
                node->pai->cor = 1;

                node = x;
            }else{
                if(node == node->pai->esq){
                    node = node->pai;
                    rotacaodir(raiz, node);    
                }
                node->pai->cor= 0;
                node->pai->pai->cor = 1;
                rotacaoesq(raiz, node);
            }
        }

    }
    (*raiz)->cor = 1;

}


void inserirNo(struct NoRb **root, int valor){

    struct NoRb *novoNo = criarNo(valor); // cria um novo No com o valor inserido
    struct NoRb *paiX = NULL; // Valor para armazenar o pai
    struct NoRb *x = *root; // Variavel para percorrer arvore

    while(x != NULL){
        paiX = x; //  Armazena o pai do No atual

        // Percorrendo arvore até achar o lugar certo para o novo No
        if (novoNo->dado < x->dado){
            x = x->esq;
        } else if  (novoNo->dado > x->dado){
            x = x->dir;
        } else{
            free(novoNo);
            return;
        }
    }
    //  Insere o novo pai do No
    novoNo->pai = paiX;

    //Inserindo Novo No
    if(paiX == NULL){
        *root = novoNo;
    }else if( novoNo->dado < paiX->dado ){
        paiX->esq = novoNo;
    }else{
        paiX->dir = novoNo;
    }

    // Balanceando Arvore
    balancear(root, novoNo);

};

// Função para imprimir a árvore Red-Black em ordem
void emOrdem(struct NoRb *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esq);
        if (raiz->cor == 0)
            printf("%d RED", raiz->dado);
        else
            printf("%d BLK", raiz->dado);
        emOrdem(raiz->dir);
    }
}

// Função para imprimir a árvore de acordo com o formato esquerda-raiz-direita segundo Sedgewick
void imprimeArvoreRB(struct NoRb *raiz, int b)
{
    if (raiz != NULL)
    {
        // Chama a função recursivamente para percorrer a subárvore direita
        imprimeArvoreRB(raiz->dir, b + 1);

        // Imprime o valor do nó atual com um espaçamento proporcional à sua profundidade
        for (int i = 0; i < b; i++)
            printf("       "); // espaços por nível
        if (raiz->cor == 0)
            printf("\033[31m%d\033[0m\n\n", raiz->dado);
        else
            printf("%d\n\n", raiz->dado);

        // Chama a função recursivamente para percorrer a subárvore esquerda
        imprimeArvoreRB(raiz->esq, b + 1);
    }
}

int main()
{
    struct No *raiz = NULL;
    // Exemplo de inserção de valores na árvore Red-Black
    int vetor[] = {12, 31, 20, 17, 11, 8, 3, 24, 15, 33};
    int i, tam = sizeof(vetor) / sizeof(vetor[0]);
    for (i = 0; i < tam; i++)
        inserir(&raiz, vetor[i]);
    printf("Árvore Red-Black: \n");
    imprimeArvoreRB(raiz, 3);
    printf("\n");

    return 0;
}




