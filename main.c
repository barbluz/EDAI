#include <stdio.h>
#include "avl.h"

void insere(arv* A);

void consulta(arv* A);

void ranca(arv* A);

void imprime_ordem(arv* A);

void imprime_nivel(arv* A);

void imprime_altura(arv* A);

void crescente(no* raiz);

void decrescente(no* raiz);

void percorre_nivel(no* raiz, int target, int qnt);

int main() {
    char op;
    arv* A = inicializa_arvore();

    while (scanf("%c", &op), op != 'f') {
        switch (op) {
            case 'i':
                insere(A);
            break;

            case 'c':
                consulta(A);
            break;

            case 'r':
                ranca(A);
            break;

            case 'p':
                imprime_ordem(A);
            break;

            case 'n':
                imprime_nivel(A);
            break;

            case 'h':
                imprime_altura(A);
            break;

        }
    }
    // termino_entrada();
}

void insere(arv* A) {
    int codigo_cliente, op, val;
    scanf(" %i %i %i", &codigo_cliente, &op, &val);
    insere_no(A, codigo_cliente, op, val);
}

void consulta(arv* A) {
    int codigo_cliente;
    scanf("%i", &codigo_cliente);
    if (!consulta_no(A, codigo_cliente)) {
        printf("nao ");
    }
    printf("existe no com chave: %i", codigo_cliente);
}

void imprime_ordem(arv* A) {
    char c;
    scanf (" %c", &c);
    if (c == 'c') {
        crescente(A->raiz);
    }
    else if (c == 'd') {
        decrescente(A->raiz);
    }
}
void imprime_nivel(arv* A) {
    int target;
    scanf("%d", &target);
    percorre_nivel(A->raiz, target, 1);
}

void ranca(arv* A) {
    int codigo_cliente;
    scanf("%i", &codigo_cliente);
    if (consulta_no(A, codigo_cliente)) {
//        remove_no(A, codigo_cliente)
    }
}

void imprime_altura(arv* A) {
    printf("%i\n", altura(A->raiz));
}

void crescente(no* raiz) {
    if (raiz == NULL) return;
    else {
        crescente(raiz->esq);
        printf("%d\n", raiz->fb);
        crescente(raiz->dir);
    }
}

void decrescente(no* raiz) {
    if (raiz == NULL) return;
    else {
        decrescente(raiz->dir);
        printf("%d\n", raiz->codigo_cliente);
        decrescente(raiz->esq);
    }
}

void percorre_nivel(no* raiz, int target, int qnt) {
    if (raiz == NULL) return;
    else if (target == qnt) {
        printf("%d ", raiz->codigo_cliente);
    }
    else {
        percorre_nivel(raiz->dir, target, qnt+1);
        percorre_nivel(raiz->esq, target, qnt+1);
    }
} 
    