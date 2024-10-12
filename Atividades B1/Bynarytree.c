#include <stdio.h>
#include <stdlib.h>

/**
Paulo Rhyan Kuster - CC6N

• Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
• Escreva funções que recebam um ponteiro para a raiz da árvore e façam:
   1 • Inserção de um elemento na árvore;
   2 • Pesquisa de um elemento na árvore;
   3 • Exclusão de um elemento na árvore.

 **/

struct Noarvore
{
    int dado;
    struct Noarvore *esq;
    struct Noarvore *dir;
};

// Criando arvore
struct Noarvore *criarRaiz(int dado)
{
    struct Noarvore *novoNo =(struct Noarvore *)malloc(sizeof(struct Noarvore)); // Alocando espaço na memória
    if(novoNo == NULL) // Verificando se a alocação foi bem sucedida
    {
        printf("Erro ao alocar memoria");
        exit(-1);
    }
    novoNo->dado = dado;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}


// Função 1: Inserir elemento
struct Noarvore *inserirNo(struct Noarvore *raiz, int dado) 
{
    if(raiz == NULL)
    {
        raiz = criarRaiz(dado);
    }
    else
    {
        if(dado <= raiz->dado)
        {
            raiz->esq = inserirNo(raiz->esq, dado);
        }
        else
        {
            raiz->dir = inserirNo(raiz->dir, dado);
        }
    }
    return raiz;
}


// Função 2 : Pesquisar Elemento
struct Noarvore *pesquisar(struct Noarvore *raiz, int valor)
{
    if (raiz == NULL || raiz->dado)
    {
        return raiz;
    }
    else if (valor < raiz->dado)
    {
        return pesquisar(raiz->esq, valor);
    }
    else
    {
        return pesquisar(raiz->dir, valor);
    }
}


// Função para entrar o valor mais a esquerda raiz, usada para usar o valor que vai substituir a raiz quando a excluirmos
struct Noarvore *encontrarMinimo(struct Noarvore *raiz)
{
    struct Noarvore *atual = raiz;
    while (atual->esq != NULL)
    {
        atual = atual->esq;
    }
    return atual;
}


// Função 3: Excluir valor
struct Noarvore *excluirNo(struct Noarvore *raiz, int valor)
{
    if (raiz == NULL) // Quando o valor não esta na arvore
    {
        printf("Valor não está na arvore");
        return raiz;
    }   

    if (valor < raiz->dado)
    {
        raiz->esq = excluirNo(raiz->esq, valor);
    }
    else if(valor > raiz->dado)
    {
        raiz->dir = excluirNo(raiz->dir, valor);
    }
    else
    {
        // Nó folha ou com apenas um filho
        if(raiz->esq == NULL)
        {
            struct Noarvore *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if(raiz->dir == NULL)
        {
            struct Noarvore *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Raiz com dois filhos
        struct Noarvore *temp = encontrarMinimo(raiz->dir); // Encontrando o menor valor a direita que é o que pode subtituir a raiz
        raiz->dado = temp->dado;
        raiz->dir = excluirNo(raiz->dir, temp->dado);

    }
    return raiz;
    
}

// Função auxiliar para imprimir arvore
void imprimirno(int a, int b)
{
    int i;
    for(i = 0; i < b; i++)
    {
        printf("  ");
    }
    printf("%i\n", a);
}

// Função para mostrar arvore
void mostrararvore(struct Noarvore *a, int b)
{
    if(a == NULL){
        return;
    }
    mostrararvore(a->dir, b+1);
    imprimirno(a->dado, b);
    mostrararvore(a->esq, b + 1);
    
}



int main(){
    struct Noarvore *arvore = NULL;

    arvore = inserirNo(arvore, 5);
    arvore = inserirNo(arvore, 7);
    arvore = inserirNo(arvore, 3);
    arvore = inserirNo(arvore, 4);
    arvore = inserirNo(arvore, 1);
    arvore = inserirNo(arvore, 9);
    arvore = inserirNo(arvore, 11);

    mostrararvore(arvore, 6);
    printf("Excluindo 11...\n");
    excluirNo(arvore, 11);
    mostrararvore(arvore, 6);

    return 0;
};
