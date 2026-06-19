#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "polyapprox.h"
#include "types.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: polyapprox <critério> <valor de tolerância>\n");
        return 1;
    }

    const char *criterio_str = argv[1];
    const float tolerancia = atof(argv[2]);

    Criterio criterio;

    // determina o critério a ser usado com base no argumento de linha de comando
    if (strcmp(criterio_str, "-a") == 0) {
        criterio = CRITERIO_AREA;
    } else if (strcmp(criterio_str, "-h") == 0) {
        criterio = CRITERIO_ALTURA;
    } else {
        printf("Opção inválida.\n");
        return 1;
    }

    // chama a função principal do programa
    polyapprox(criterio, tolerancia);

    return 0;
}

