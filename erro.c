#include <stdio.h>
#include <stdlib.h>

#include "erro.h"
#include "avl.h"
#include "types.h"

float area_triangulo(float x1, float y1, float x2, float y2, float x3, float y3) {
    float area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
    if (area < 0)
        area = -area;
    return area;
}

float altura2_triangulo(float x1, float y1, float x2, float y2, float x3, float y3) {
    float area, dx, dy;
    area = area_triangulo(x1, y1, x2, y2, x3, y3);
    dx = x3 - x1;
    dy = y3 - y1;
    return 4 * (area * area)/(dx * dx + dy * dy);
}

// decide qual fórmula de erro aplicar com base no critério escolhido
// (-a usa área do triângulo, -h usa altura² do triângulo)
float calcula_erro(No *a1, No *a2, No *a3, Criterio criterio){
    if (criterio == CRITERIO_AREA){
        return area_triangulo(a1->x, a1->y, a2->x, a2->y, a3->x, a3->y);
    } else{
        return altura2_triangulo(a1->x, a1->y, a2->x, a2->y, a3->x, a3->y);
    }
}