#ifndef MINHEAP_H
#define MINHEAP_H

#include "avl.h"

typedef struct heap{
    int tam;
    int capacidade;
    struct No **no;
}heap;

int HeapVazio(heap *h);

heap *cria_heap(int capacidade);

int InsereHeap(heap *h, No *n);

No *HeapMinino(heap *h);

No *RemoveHeap(heap *h);

void AtualizaHeap(heap *h, int pos_heap, float novo_erro);

void ImprimeHeap(heap *h);

void DestroiHeap(heap *h);

#endif