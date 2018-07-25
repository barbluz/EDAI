#ifndef avl
#define avl

typedef struct no {
    int codigo_cliente;
    int qt_op;
    int saldo;
    int fb;
    struct no *esq, *dir, *pai;
} no;

typedef struct arv {
    no* raiz;
    int tam;
} arv;

arv* inicializa_arvore();

no* cria_no (int cod, int val );

void insere_no (arv* A, int cod, int op, int val);

void atualiza_fb (no* node);

void balanceia (arv* A, no* node);

void atualiza_valor (no* node, int op, int val);

int consulta_no (arv* A, int cod);

int max (int a, int b);

int altura (no* raiz);

void rot_esq (arv* A, no* node);

void rot_dir (arv* A, no* node);

no* ranca_no (arv* A, no* node, int k);

no* sucessor (no* node);

#endif