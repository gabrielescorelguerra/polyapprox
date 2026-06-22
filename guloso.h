#ifndef GULOSO_H
#define GULOSO_H
#include "avl.h"
#include "minheap.h"

//algoritmo guloso de eliminação iterativa
void guloso_simplificar(AVL *avl, heap *heap, float tolerancia, Criterio criterio);

#endif