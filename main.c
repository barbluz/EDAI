#include <stdio.h>
#include "avl.h"

int main() {
    char op;

    while (scanf("%c", &op), op != 'f') {
        switch (op) {
            case 'i':
                insere_no();
            break;

            case 'c':
                consulta_no();
            break;

            case 'r':
                remove_no();
            break;

            case 'p':
                imprime_ordem();
            break;

            case 'n':
                lista_nivel();
            break;

            case 'h':
                altura();
            break;

        }
    }
    termino_entrada();
}
