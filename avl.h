// Desenvolvido por Bárbara Gabriele Lima Luz Santos, Micael de Oliveira Mota e Rafael Correa Nagy

#ifndef avl
#define avl

typedef struct no {
    int codigo_cliente;
    int qt_op;
    int saldo;
    struct no *esq, *dir, *pai;
} no;

typedef struct arv {
    no* raiz;
    int tam;
} arv;


/*
 * Função inicializa_arvore:
 * Aloca o espaço de memória para uma nova árvore AVL. Retorna um ponteiro para a árvore AVL criada.
 *
 * */
arv* inicializa_arvore();


/*
 * Função cria_no:
 * Cria um nó de árvore. Retorna um ponteiro para o nó criado.
 *
 * */
no* cria_no (int cod, int val);


/*
 * Função insere_no:
 * Insere um novo nó na árvore e realiza o balanceamento ou atualiza o campo "saldo" do nó existente.
 *
 * */
void insere_no (arv* A, int cod, int op, int val);


/*
 * Função balanceia:
 * Balanceia a árvore após inserção ou remoção de um nó.
 *
 * */
void balanceia (arv* A, no* node);


/*
 * Função atualiza_valor:
 * Atualiza o campo "saldo" de um nó de acordo com a operação passada como parâmetro.
 *
 * */
void atualiza_valor (no* node, int val);


/*
 * Função consulta_no:
 * Verifica a existência de um nó na AVL. Retorna 0 caso o nó não exista e retorna 1 caso exista.
 *
 * */
int consulta_no (arv* A, int cod);


/*
 * Função max:
 * Dados dois inteiros, retorna o maior.
 *
 * */
int max (int a, int b);


/*
 * Função altura:
 * Calcula a altura de um nó na árvore.
 *
 * */
int altura (no* raiz);


/*
 * Função rot_esq:
 * Realiza rotação simples à esquerda em um nó.
 *
 * */
void rot_esq (arv* A, no* node);


/*
 * Função rot_dir:
* Realiza rotação simples à direita em um nó. 
 *
 * */
void rot_dir (arv* A, no* node);


/*
 * Função ranca_no:
 * Remove um nó da árvore. Retorna um ponteiro para o nó removido.
 *
 * */
no* ranca_no (arv* A, no* node, int k);


/*
 * Função sucessor:
 * Retorna o sucessor de um nó na árvore.
 *
 * */
no* sucessor (no* node);

#endif
