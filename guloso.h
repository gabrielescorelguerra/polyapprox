#ifndef GULOSO_H
#define GULOSO_H
#include "avl.h"
#include "minheap.h"

// calcula o erro de remover o ponto a2, usando a1 e a3 como vizinhos,
// de acordo com o critério escolhido (área ou altura²)
float calcula_erro(No *a1, No *a2, No *a3, Criterio criterio);

//algoritmo guloso de eliminação iterativa
void guloso_simplificar(AVL *avl, heap *heap, float tolerancia, Criterio criterio);

#endif