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
            node->pai = y;
            atualiza_fb(y);
            balanceia(A, y);
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

void balanceia (arv* A, no* node) {
    if (node == NULL) {
        return;
    } 
    else {
        if (node->fb == 2) {
            if (node->esq->fb != -1) {
                rot_dir(A, node);
            } else {
                rot_esq(A, node->esq);
                rot_dir(A, node);
            }
        } 
        else if (node->fb == -2) {
            if (node->dir->fb != 1) {
                rot_esq(A, node);
            } 
            else {
                rot_dir(A, node);
                rot_esq(A, node);
            }
        }
        atualiza_fb(node);
        balanceia(A, node->pai);
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


void rot_esq (arv* A, no* node){
    no* aux = node->dir;
    node->dir = aux->esq;
    if (aux->esq != NULL) {
        aux->esq->pai = node;
    }
    aux->esq = node;
    aux->pai = node->pai;
    if (A->raiz == node) {
        A->raiz = aux;
    }
    else{
        if (node->pai->dir == node) {
            node->pai->dir = aux;
        }
        else {
            node->pai->esq = aux;
        }
    }
    node->pai = aux;
}


void rot_dir (arv* A, no* node) {
    no* aux = node->esq;
    node->esq = aux->dir;
    if (aux->dir != NULL) {
        aux->dir->pai = node;
    }
    aux->dir = node;
    aux->pai = node->pai;
    if (A->raiz == node) {
        A->raiz = aux;
    }
    else {
        if (node->pai->dir == node) {
            node->pai->dir = aux;
        }
        else {
            node->pai->esq = aux;
        }
    }
    node->pai = aux;
}

no* ranca_no (arv* A, no* node, int k) {
    if (node == NULL)
        return NULL;
    if (node->codigo_cliente < k) {
        return ranca_no(A, node->dir, k);
    }
    else if (node->codigo_cliente > k) {
        return ranca_no(A, node->esq, k);
    }
    else {
        no* removido = node;
        //FOLHA
        if (node->dir == NULL && node->esq == NULL) {
            if (A->raiz == node) {
                A->raiz = NULL;
            }
            else if (node->pai->dir == node) {
                node->pai->dir = NULL;
            }
            else {
                node->pai->esq = NULL;
            }
            atualiza_fb(node->pai);
            balanceia(A, node->pai);
        }
        //UM FILHO NA ESQ
        else if (node->dir == NULL) {
            if (A->raiz == node) {
                A->raiz = node->esq;
                node->esq->pai = NULL;
            }
            else if (node->pai->dir == node) {
                node->pai->dir = node->esq;
                node->esq->pai = node->pai;
            }
            else {
                node->pai->esq = node->esq;
                node->esq->pai = node->pai;
            }
            atualiza_fb(node->esq);
            balanceia(A, node->esq);
        }
        //UM FILHO NA DIR
        else if (node->esq == NULL) {
            if (A->raiz == node) {
                A->raiz = node->dir;
                node->dir->pai = NULL;
            }
            else if (node->pai->dir == node) {
                node->pai->dir = node->dir;
                node->dir->pai = node->pai;
            }
            else {
                node->pai->esq = node->dir;
                node->dir->pai = node->pai;
            }
            atualiza_fb(node->dir);
            balanceia(A, node->dir);
        }
        //DOIS FILHOS
        else {
            no* suc = sucessor(node);
            no* aux = suc->pai;
            if (node->dir == suc)
                aux = suc;
            //DOIS FILHOS E RAIZ
            if (A->raiz == node) {
                A->raiz = suc;
                if (node->dir != suc) {
                    if (suc->dir != NULL) { 
                        suc->dir->pai = suc->pai;
                    }
                    suc->pai->esq = suc->dir;
                } 
                suc->pai = NULL;
            }
            //DOIS FILHOS E NAO RAIZ
            else {
                if (node->pai->dir == node) {
                    node->pai->dir = suc;
                    if (node->dir != suc) {
                        suc->pai->esq = suc->dir;
                        if (suc->dir) {
                            suc->dir->pai = suc->pai;
                        }
                        node->pai->dir = suc->dir;
                    }
                    suc->pai = node->pai;
                }
                else {
                    node->pai->esq = suc;
                    if (node->dir != suc) {
                        suc->pai->esq = suc->dir;
                        if (suc->dir) suc->dir->pai = suc->pai;
                        node->pai->dir = suc->dir;
                    }
                    suc->pai = node->pai;
                }
            }
            
            suc->esq = node->esq;
            if (suc->esq) suc->esq->pai = suc;
            if (node->dir != suc) {
                suc->dir = node->dir;
                if (suc->dir) suc->dir->pai = suc;
            }
            atualiza_fb(aux);
            balanceia(A, aux);
        }
        return removido;
    }
}

no* sucessor (no* node) {
    if (node == NULL && node->dir != NULL) {
        return NULL;
    }
    no* aux = node->dir;
    while (aux->esq != NULL) {
        aux = aux->esq;
    }
    return aux;
}