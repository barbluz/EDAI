#ifndef avl
#define avl

typedef struct no {
    int codigo_cliente;
    int qt_op;
    int saldo;
    no* esq, dir, pai;
} no;

typedef struct arv {
    no* raiz;
    int tam;
} arv;

void inicializa_arvore(arv* a);

no* cria_no(int cod, bool op, bool val);

void rot_esq(arv* a, no* cliente);

void rot_dir(arv* a, no* cliente);

void rot_dupl_esq(arv* a, no* cliente);

void rot_dupl_dir(arv* a, no* cliente);

void insere_no(arv* a, no* cliente);

void consulta_no(arv a, int cod);

void remove_no(arv* a, int cod);

void imprime_ordem(arv a);

int altura(arv a);

void termino_entrada(arv a);

