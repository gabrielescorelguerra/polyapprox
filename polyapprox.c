#include <stdio.h>

#include "polyapprox.h"
#include "types.h"
#include "avl.h"
#include "minheap.h"
#include "erro.h"
#include "guloso.h"

// inicializa estruturas de dados e popula com os pontos lidos
static void polyapprox_init(AVL *avl, heap *heap, Criterio criterio, int quantidade_inicial) {
    No *ultimo = NULL;

    // inserir pontos na avl, setando ponteiros ant e prox de cada no (lista encadeada entre eles)
    for (int i = 0; i < quantidade_inicial; i++) {
        float y;
        scanf("%f", &y);

        No *p = no_criar(i + 1, y);

        p->ant = ultimo;
        if (ultimo != NULL)
            ultimo->prox = p;
        ultimo = p;

        avl_inserir(avl, p);
    }

    No *head = arvore_minimo(avl->raiz);
    head = head->prox;

    // calcular erros e inserir no heap , ele vai conter so os pontos removiveis
    while (head->prox != NULL) {
        head->erro = calcula_erro(head->ant, head, head->prox, criterio);
        InsereHeap(heap, head);
        head = head->prox;
    }
}


void polyapprox(Criterio criterio, float tolerancia ) { 
    int quantidade_inicial;
    scanf("%d", &quantidade_inicial);

    AVL *avl = avl_criar();
    heap *heap = cria_heap(quantidade_inicial);
    if (avl == NULL || heap == NULL) {
        printf("Erro ao alocar memória para estruturas de dados.\n");
        return;
    }

    polyapprox_init(avl, heap, criterio, quantidade_inicial);

    guloso_simplificar(avl, heap, tolerancia, criterio);

    printf ("%d\n", (heap->tam + 2));
    inorder_tree_walk(avl);

    DestroiHeap(heap);
    avl_destruir(avl);
}
