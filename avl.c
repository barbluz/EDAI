    #include <stdio.h>
#include "avl.h"

arv* inicializa_arvore() {
    arv* a = (arv*)malloc(sizeof(arv));
    a->raiz = NULL;
    a->tam = 0;
    return a;
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



void insere (avl* A, int cod, bool op, int val) {
    no* x, y;
    x = A->raiz;
    y = x;
    while (x != NULL && x->codigo_cliente != cod) {
        y = x;
        if (x->chave > cod) {
            x = x->esq;
        }
        else {
            x = x->dir;
        }
    }

    if (x == NULL) {
        no* node = cria_no(cod, op, val);
        if (y->chave > cod) {
            y->esq = node;
        }
        else {
            y->dir = node;
        }
        insere(A, node);
        atualiza_fb(node);
        balanceia(node);
        
    }

    else {
        atualiza_valor(x, op, val);
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
    if (node == NULL) {
        return;
    } else {
        if (node->fb > 1) {
            if (node->esq->fb >= 0) {
                rot_dir(node);
            } else {
                rot_esq(node->esq);
                rot_dir(node);
            }
        } else if (node->fb < -1) {
            if (node->dir->fb <= 0) {
                rot_esq(node);
            } else {
                rot_dir(node->dir);
                rot_esq(node);
            }
        }
        balanceia(node->pai);
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

tuple consulta_no (no* raiz, int cod) {
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

int altura (no* raiz) {
    int e, d;
    if (raiz == NULL) {
        return 0;
    } else {
        e = altura(raiz->esq);
        d = altura(raiz->dir);
        return (max(e, d)+1);
    }
}



void rot_esq (no* a) {
    no* b = a->dir;
    no* pai = a->pai;
    if (pai->esq == a) 
        pai->esq = b;
    else
        pai->dir = b;
    b->pai = pai;
    b->esq->pai = a;
    a->dir = b->esq;
    a->pai = b;
    b->esq = a;
}

void rot_dir (no* a) {
    no* b = a->esq;
    no* pai = a->pai;
    if (pai->esq == a) 
        pai->esq = b;
    else
        pai->dir = b;
    b->pai = pai;
    b->dir->pai = a;
    a->esq = b->dir;
    a->pai = b;
    b->dir = a;
}