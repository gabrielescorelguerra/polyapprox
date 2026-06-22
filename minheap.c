#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minheap.h"
#include "avl.h"


int HeapVazio(heap *h) {
    if(h == NULL || h->tam < 1)
        return 1;
    return 0;
}

heap *cria_heap(int capacidade) {
    heap *h = malloc(sizeof(struct heap));
    if (h == NULL)
        return NULL;
    h->tam = 0;
    h->capacidade = capacidade;
    h->no = malloc((capacidade + 1) * sizeof(No *));
    return h;
}

int InsereHeap(heap *h, No *n) {
    int i;
    struct No *aux;

    i = h->tam + 1;
    if (i > h->capacidade)
        return 0;

    h->no[i] = n;
    h->no[i]->pos_heap = i;
    h->tam++;

    while(i > 1 && h->no[i/2]->erro > h->no[i]->erro) {
        aux = h->no[i];
        h->no[i] = h->no[i/2];
        h->no[i/2] = aux;
        h->no[i]->pos_heap = i;
        h->no[i/2]->pos_heap = i/2;
        i = i / 2;
    }
    return 1; 
}

void DesceNoHeap(heap *h, int pai) {
    int menor = pai;
    int esq = 2 * pai;
    int dir = 2 * pai + 1;
    No *aux;

    if (esq <= h->tam && h->no[esq]->erro < h->no[menor]->erro) {
        menor = esq;
    }
    if (dir <= h->tam && h->no[dir]->erro < h->no[menor]->erro) {
        menor = dir;
    }

    if (menor != pai) {
        aux = h->no[pai];
        h->no[pai] = h->no[menor];
        h->no[menor] = aux;

        h->no[pai]->pos_heap = pai;
        h->no[menor]->pos_heap = menor;

        DesceNoHeap(h, menor);
    }
}

void SobeNoHeap(heap *h, int i){
    No *aux;
    while(i > 1 && h->no[i/2]->erro > h->no[i]->erro) {
        aux = h->no[i];
        h->no[i] = h->no[i/2];
        h->no[i/2] = aux;
        h->no[i]->pos_heap = i;
        h->no[i/2]->pos_heap = i/2;
        i = i / 2;
    }
}

void Heapify(heap *h) {
    if (h == NULL || h->tam <= 1) 
        return;

    for (int i = h->tam / 2; i >= 1; i--) {
        DesceNoHeap(h, i);
    }
}

No *HeapMinino(heap *h) {
    if (HeapVazio(h))
        return NULL;
    return h->no[1];
}

No *RemoveHeap(heap *h) {
    No *n;
    if (HeapVazio(h)){
        return NULL;
    }

    n = h->no[1];
    if (h->tam == 1){
        h->tam--;
        return n;
    }

    h->no[1] = h->no[h->tam];
    h->no[1]->pos_heap = 1;
    h->tam--;
    DesceNoHeap(h, 1);
    return n;
}

void AtualizaHeap(heap *h, int pos_heap, float novo_erro) {
    if (h == NULL || h->tam < 1 || pos_heap < 1 || pos_heap > h->tam)
        return;
    float erro_antes = h->no[pos_heap]->erro;
    h->no[pos_heap]->erro = novo_erro;

    if (erro_antes < novo_erro){
        DesceNoHeap(h, pos_heap);
        return;
    }
    else if (erro_antes > novo_erro){
        SobeNoHeap(h, pos_heap);
        return;
    }
}

void ImprimeHeap(heap *h) {
    int i;

    if(HeapVazio(h))
        printf("Fila vazia");
    printf("capacidade: %d \n", h->capacidade);
    printf("tamanho: %d \n", h->tam);
    for(i=1; i<=h->tam; i++)
        printf("(%f %f) %f, %d\n", h->no[i]->x, h->no[i]->y, h->no[i]->erro, h->no[i]->pos_heap);
}

void DestroiHeap(heap *h) {
    if (h == NULL)
        return;
    free(h->no);
    free(h);
}