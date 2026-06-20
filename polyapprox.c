#include <stdio.h>

#include "polyapprox.h"
#include "types.h"
#include "avl.h"


// função de erro a ser usada para calcular o erro de um ponto, dependendo do critério escolhido
typedef float (*FuncaoErro)(float, float, float, float, float, float);

// também é pra ter um meio de o heap se comunicar com a avl, para
// atualizar a posição de um ponto na avl sempre que ele mudar de
// posição no heap (em qualquer swap interno: inserção, extração do
// mínimo, ou atualização de prioridade)


// inicializa estruturas de dados e popula com os pontos lidos
static void polyapprox_init(FuncaoErro calcular_erro, AVL *avl/*Heap *heap*/) {
    int count;
    scanf("%d", &count);

    // prox e ult so funciona se colocar em ordem
    No *ultimo = NULL;

    // inserir pontos na avl, setando ponteiros ant e prox de cada no (lista encadeada entre eles)
    for (int i = 0; i < count; i++) {
        float x, y;
        scanf("%f %f", &x, &y);

        No *p = no_criar(x, y);

        p->ant = ultimo;
        if (ultimo != NULL)
            ultimo->prox = p;
        ultimo = p;

        avl_inserir(avl, p);
    }

    inorder_tree_walk(avl);

    // calcular erros e inserir no heap , ele vai conter so os pontos removiveis
    for (int i = 2; i < count - 1; i++) {
        // calcular erro ponto i - 1 (usa i - 2, i - 1, i), com a funcao passada para calcular erro
        // coloca no heap
        // atualiza posicao pos_heap do ponto i - 1 na avl
    }

    // a insercao dos pontos na avl e no heap, cada um, esta dentro do limite de O(n log n)
    
}

// escolhe a função de erro a ser usada com base no critério escolhido
static FuncaoErro escolher_funcao_erro(Criterio criterio) {
    switch (criterio) {
        case CRITERIO_AREA:
            return NULL; // vai retornar funcao de erro que calcula area do triangulo formado por 3 pontos
        case CRITERIO_ALTURA:
            return NULL; // vai retornar funcao de erro que calcula altura do triangulo formado por 3 pontos
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


void polyapprox(Criterio criterio, float tolerancia) { 
    AVL *avl = avl_criar();
    // cria heap

    FuncaoErro funcao_erro = escolher_funcao_erro(criterio);

    polyapprox_init(funcao_erro, avl /*heap*/);

    // imprimir saida

    avl_destruir(avl);
    // destroi heap
}

// no tad avl eh bom ter a quantidade de pontos, porque no final vai ter que imprimir
