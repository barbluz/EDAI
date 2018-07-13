#include <stdio.h>
#include "avl.h"

void inicializa_arvore(arv* a) {
    a->raiz = NULL;
    a.tam = 0;
}

no* cria_no(int cod, bool op, int val ) {
    no* node = (no*)malloc(sizeof(no));
    node->codigo_cliente = cod;
    node->qt_op = 1;
    node->saldo = val;
    node->fb = 0;
    node->esq = NULL;
    node->dir = NULL;
    node->pai = NULL;
    return node;
}

void insere (no* raiz, int cod, bool op, int val) {
    tuple t = consulta_no(raiz, cod);
    if (!t.desejado) {
        no* node = cria_no(cod, op, val);
        insere_no(&raiz, &node, t);
        atualiza_fb(&node);
        balanceia(&node);
    } else {
        atualiza_valor(&t.desejado, op, val);
    }
}

void insere_no (no* raiz, no* node, tuple t) {
    if(raiz == NULL) {
        raiz = node;
        node->pai = t.anterior;
    } else {
        if (node->codigo_cliente < raiz->codigo_cliente ) {
            insere_no(raiz->esq, node);
        } else {
            insere_no(raiz->dir, node);
        }
    }
}

void atualiza_fb(no* node) {
    if (node == NULL) {
        return;
    } else {
        node->fb = (altura(node->esq) - altura(node->dir));
        atualiza_fb(node->pai);
    }
}

void balanceia(no* node) {
    if (node->pai == NULL) {
        return;
    } else {
        if (node->pai->fb > 1) {
            if (node->fb >= 0) {
                rot_dir(&node->pai, &node);
            } else {
                rot_ddir(&node->pai, &node);
            }
        } else if (node->pai->fb < -1) {
            if (node->fb < 0) {
                rot_esq(&node->pai, &node);
            } else {
                rot_desq(&node->pai, &node);
            }
        }
        balanceia(&node->pai);
    }
}

void atualiza_valor(no* node, bool op, int val) {
    if (op == 0) {
        node->saldo += val;
    } else {
        node->saldo -= val;
    }
    node->qt_op++;
}

tuple consulta_no (no raiz, int cod) {
    tuple result;
    result.anterior = NULL;
    result.desejado = NULL;

    if (raiz == NULL) {
        return result;
    } else {
        while (raiz->codigo_cliente != cod) {
            if (cod < raiz->codigo_cliente) {
                result.anterior = raiz;
                consulta_no(raiz->esq, cod);
            }
            else {
                result.anterior = raiz;
                consulta_no(raiz->dir, cod);
            }
        }
        result.desejado = raiz;
        return result;
    }
}

int max (int a, int b) {
    if (b > a) {
        return b;
    } else return a;
}

int altura (no raiz) {
    int e, d;
    if (raiz == NULL) {
        return 0;
    } else {
        e = altura(raiz->esq);
        d = altura(raiz->dir);
        return (max(e, d)+1);
    }
}
