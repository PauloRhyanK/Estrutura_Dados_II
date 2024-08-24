#include <stdio.h>
#include <stdlib.h>

/*
Paulo Rhyan Kuster - CC6N

• Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
• Escreva funções que recebam um ponteiro para a raiz da árvore e façam:
    • o caminhamento pré-ordem
    • o caminhamento pós-ordem
    • o caminhamento central
*/

struct Noarvore
{
    int dado;
    struct Noarvore *esq;
    struct Noarvore *dir;
};

struct Noarvore *criaRaiz(int dado)
{
    struct Noarvore *raiz = (struct Noarvore *)malloca(sizeof(struct Noarvore));
    if (raiz = NULL)
    {
        printf("Erro ao alocar memoria");
        exit(-1);
    }
    raiz->dado = dado;
    raiz->esq = NULL;
    raiz->dir = NULL;
}


