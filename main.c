#include <stdio.h>
#include "avl.h"

int main() {
    char op;
    arv* A = inicializa_arvore();

    while (scanf("%c", &op), op != 'f') {
        switch (op) {
            case 'i':
                insere(A);
            break;

            case 'c':
                crescente(A->raiz);
            break;

            case 'r':
                // remove();
            break;

            case 'p':
                // imprime_ordem();
            break;

            case 'n':
                // lista_nivel();
            break;

            case 'h':
                // altura();
            break;

        }
    }
    // termino_entrada();
}
