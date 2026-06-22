#include <math.h>
#include "guloso.h"
#include "erro.h"
#include <stdio.h>

// decide qual fórmula de erro aplicar com base no critério escolhido
// (-a usa área do triângulo, -h usa altura² do triângulo)
float calcula_erro(No *a1, No *a2, No *a3, Criterio criterio){
    if (criterio == CRITERIO_AREA){
        return area_triangulo(a1->x, a1->y, a2->x, a2->y, a3->x, a3->y);
    } else{
        return altura2_triangulo(a1->x, a1->y, a2->x, a2->y, a3->x, a3->y);
    }
}

void guloso_simplificar(AVL *avl, heap *heap, float tolerancia, Criterio criterio){
    while(!HeapVazio (heap)){
        // ponto de menor erro
        No *p = HeapMinino(heap);

        if (p->erro >= tolerancia){
                break;
        }

        // remove o ponto do heap
        p = RemoveHeap(heap);

        // salva os outros nós
        No *ant = p->ant;
        No *prox = p->prox;

        // atualiza a lista duplamente encadeada
        if (ant != NULL){
            ant->prox = prox;
        }
        if (prox != NULL){
            prox->ant = ant;
        }

        // remove da avl
        avl_remover(avl, p);

        // recalcula o erro do ponto ant e atualiza no heap
        if (ant != NULL && ant->ant != NULL){
            float novo_erro_ant = calcula_erro(ant->ant, ant, ant->prox, criterio);
            AtualizaHeap(heap, ant->pos_heap, novo_erro_ant);
        }

        // recalcula o erro do ponto prox e calcula no heap
        if (prox != NULL && prox->prox != NULL){
            float novo_erro_prox = calcula_erro(prox->ant, prox, prox->prox, criterio);
            AtualizaHeap(heap, prox->pos_heap, novo_erro_prox);
        }
    }
}
