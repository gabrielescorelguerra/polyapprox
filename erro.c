#include <stdio.h>
#include <stdlib.h>

#include "erro.h"
#include "avl.h"

float area_triangulo(No *a1, No *a2, No *a3){
    float area = (a1->x * (a2->y - a3->y) + a2->x * (a3->y - a1->y) + a3->x * (a1->y - a2->y)) / 2;
    if (area < 0)
        area = -area;
    return area;
}

float altura2_triangulo(No *a1, No *a2, No *a3){
    float area, dx, dy;
    area = area_triangulo(a1, a2, a3);
    dx = a3->x - a1->x;
    dy = a3->y - a1->y;
    return 4 * (area * area)/(dx * dx + dy * dy);
}