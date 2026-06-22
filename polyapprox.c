#include <stdio.h>

#include "polyapprox.h"
#include "types.h"
#include "avl.h"
#include "minheap.h"

typedef float (*FuncaoErro)(float, float, float, float, float, float);

// inicializa estruturas de dados e popula com os pontos lidos
static void polyapprox_init(FuncaoErro calcular_erro, AVL *avl, heap *heap, int quantidade_inicial) {
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
        // head->erro = calcular_erro(head->ant->x, head->ant->y, head->x, head->y, head->prox->x, head->prox->y);
        InsereHeap(heap, head);
        head = head->prox;
    }
}

// escolhe a função de erro a ser usada com base no critério escolhido
static FuncaoErro escolher_funcao_erro(Criterio criterio) {
    switch (criterio) {
        case CRITERIO_AREA:
            return NULL; //area_triangulo;
        case CRITERIO_ALTURA:
            return NULL; //altura_triangulo;
    }
    return NULL;
}


// algoritmo guloso que remove pontos dentro da tolerância
static void polyapprox_simplificar(Criterio criterio, float tolerancia /*, avl, heap */) {
    while (1) {
        // Ponto p  = heap_minimo(heap);
        // if (p.erro >= tolerancia) ou heap_vazio(heap) break;

        // heap_extrair_minimo(heap);  

        /*
         * agora vai recalcular erros dos pontos adjacentes a p e atualizar no heap
         */

        // Ponto anterior = avl_predecessor(avl, p.x);
        // Ponto seguinte = avl_sucessor(avl, p.x);

        // avl_remover(avl, p.x);

        // recalcular erro de 'anterior' e 'seguinte' (cada um usando
        // seus próprios vizinhos, que já mudaram com a remoção de p)
        // e atualizar a prioridade deles no heap (decrease-key),
        // usando a posição guardada na avl pra cada um
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

    //FuncaoErro funcao_erro = escolher_funcao_erro(criterio);
    //if (funcao_erro == NULL) {
    //    printf("Erro: função de erro não definida para o critério escolhido.\n");
    //    return;
    //}

    polyapprox_init(NULL, /*funcao_erro,*/ avl, heap, quantidade_inicial);

    printf ("%d\n", (heap->tam + 2));
    inorder_tree_walk(avl);

    DestroiHeap(heap);
    avl_destruir(avl);
}
