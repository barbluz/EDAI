#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

arv* inicializa_arvore() {
    arv* A = (arv*)malloc(sizeof(arv));
    if (A == NULL) {
        printf("MEMORIA CHEIA\n");
        return NULL;
    }
    A->raiz = NULL;
    A->tam = 0;
    return A;
}

no* cria_no (int cod, int val) {
    no* node = (no*)malloc(sizeof(no));
    if (node == NULL) {
        printf("MEMORIA CHEIA\n");
        return NULL;
    }
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
    if (op) val *= -1;
    //PROCURA NÓ
    while (x != NULL && x->codigo_cliente != cod) {
        y = x;
        if (x->codigo_cliente > cod) {
            x = x->esq;
        }
        else {
            x = x->dir;
        }
    }
    //NAO EXISTE
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
            balanceia(A, node);
        }
        A->tam++;
    }
    //EXISTE
    else {
        atualiza_valor(x, val);
    }
}

void balanceia (arv* A, no* node) {
    if (node == NULL) {
        return;
    } 
    else {
        int fb = altura(node->esq) - altura(node->dir);
        if (fb >= 2) {
            int fbfilho = altura(node->esq->esq) - altura(node->esq->dir);
            if (fbfilho > -1) {
                rot_dir(A, node);
            } else {
                rot_esq(A, node->esq);
                rot_dir(A, node);
            }
        } 
        else if (fb <= -2) {
            int fbfilho = altura(node->dir->esq) - altura(node->dir->dir);
            if (fbfilho < 1) {
                rot_esq(A, node);
            } 
            else {
                rot_dir(A, node->dir);
                rot_esq(A, node);
            }
        }
        balanceia(A, node->pai);
    }
}

void atualiza_valor (no* node, int val) {
    node->saldo += val;
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
        A->tam--;
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
                        if (suc->dir != NULL) {
                            suc->dir->pai = suc->pai;
                        }
                    }
                    suc->pai = node->pai;
                }
                else {
                    node->pai->esq = suc;
                    if (node->dir != suc) {
                        suc->pai->esq = suc->dir;
                        if (suc->dir) suc->dir->pai = suc->pai;
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
