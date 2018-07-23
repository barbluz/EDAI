#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

arv* inicializa_arvore() {
    arv* A = (arv*)malloc(sizeof(arv));
    A->raiz = NULL;
    A->tam = 0;
    return A;
}

no* cria_no (int cod, int val ) {
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

void insere_no (arv* A, int cod, int op, int val) {
    no *x, *y;
    x = A->raiz;
    y = x;
    while (x != NULL && x->codigo_cliente != cod) {
        y = x;
        if (x->codigo_cliente > cod) {
            x = x->esq;
        }
        else {
            x = x->dir;
        }
    }
    if (x == NULL) {
        no* node = cria_no(cod, val);
        if (A->raiz == NULL) {
            A->raiz = node;
        }
        else {
            if (y->codigo_cliente > cod) {
                y->esq = node;
            }
            else {
                y->dir = node;
            }
            atualiza_fb(node);
            balanceia(node);
        }
        A->tam++;
    }
    else {
        atualiza_valor(x, op, val);
    }
}

void atualiza_fb (no* node) {
    if (node == NULL) {
        return;
    } 
    else {
        node->fb = (altura(node->esq) - altura(node->dir));
        atualiza_fb(node->pai);
    }
}

void balanceia (no* node) {
    if (node == NULL) {
        return;
    } 
    else {
        if (node->fb > 1) {
            if (node->esq->fb >= 0) {
                rot_dir(node);
            } else {
                rot_esq(node->esq);
                rot_dir(node);
            }
        } 
        else if (node->fb < -1) {
            if (node->dir->fb <= 0) {
                rot_esq(node);
            } 
            else {
                rot_dir(node->dir);
                rot_esq(node);
            }
        }
        balanceia(node->pai);
    }
}

void atualiza_valor (no* node, int op, int val) {
    if (op == 0) {
        node->saldo += val;
    } 
    else {
        node->saldo -= val;
    }
    node->qt_op++;
}

int consulta_no (arv* A, int cod) {
    if (A->raiz == NULL) {
        return 0;
    } else {
        no* node = A->raiz;
        while (node != NULL && node->codigo_cliente != cod) {
            if (cod < node->codigo_cliente) {
                node = node->esq;
            }
            else {
                node = node->dir;
            }
        }   
        if (node == NULL)
            return 0;
        else 
            return 1;
    }
}

int max (int a, int b) {
    if (b > a) {
        return b;
    } else return a;
}

int altura (no* raiz) {
    int e, d;
    if (raiz == NULL) {
        return 0;
    } 
    else {
        e = altura(raiz->esq);
        d = altura(raiz->dir);
        return (max(e, d)+1);
    }
}


void rot_esq (no* a) {
    no* b = a->dir;
    no* pai = a->pai;
    if (pai->esq == a) {
        pai->esq = b;
    }
    else {
        pai->dir = b;
    }
    b->pai = pai;
    b->esq->pai = a;
    a->dir = b->esq;
    a->pai = b;
    b->esq = a;
}

void rot_dir (no* a) {
    no* b = a->esq;
    no* pai = a->pai;
    if (pai->esq == a) {
        pai->esq = b;
    }
    else {
        pai->dir = b;
    }
    b->pai = pai;
    b->dir->pai = a;
    a->esq = b->dir;
    a->pai = b;
    b->dir = a;
}

void crescente (no* raiz) {
    if (raiz == NULL) return;
    else {
        crescente(raiz->esq);
        printf("%d\n", (*raiz).codigo_cliente);
        crescente(raiz->dir);
    }
}