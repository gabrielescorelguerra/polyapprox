#ifndef AVL_H
#define AVL_H

#define MAX(a,b) ((a)>(b)?(a):(b))
#define ALT(a) ((a == NULL)?(-1):(a->altura))

#include "types.h"

typedef struct No {
    float x;
    float y;

    int pos_heap; // posicao do ponto no heap

    int altura;
    struct No *pai;
    struct No *esq;
    struct No *dir;

    struct No *prox;
    struct No *ant;
} No;

typedef struct {
    No *raiz;
} AVL;

// inicializa árvore
AVL *avl_criar();

// libera memória alocada para a árvore e seus nós
void avl_destruir(AVL *t);

// cria nó
No* no_criar(float x_ponto, float y_ponto);

// inserção e remoção de nós na árvore AVL, com balanceamento
void avl_inserir(AVL *t, No *z);
void avl_remover(AVL *t, No *z);

void inorder_tree_walk (AVL *t);

#endif