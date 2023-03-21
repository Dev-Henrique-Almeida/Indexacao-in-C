#ifndef RB_H
#define RB_H

enum cor {VERMELHO, PRETO};

typedef struct indiceRb {
	int chave;
	int indice;
} indiceRb;

typedef struct no_rb
{
    enum cor c;
    indiceRb *dado;
    struct no_rb *esq, *dir, *pai;
    int altura;
}no_rb;

typedef no_rb *rb;

//void imprimir_elemento(No* no);

void inicializarRb(rb *raiz);

rb criar_no(indiceRb *valor);

void pre_order(rb raiz);

int cor(rb no);

int eh_esquerdo(rb no);

int eh_raiz(rb no);

rb tio(rb n);

void rotacao_simples_dir(rb* raiz, rb no, int simples);

void rotacao_simples_esq(rb* raiz, rb no, int simples);

void rotacao_dupla_dir(rb* raiz, rb no);

void rotacao_dupla_esq(rb* raiz, rb no);

void ajustar(rb* raiz, rb no);

void adicionarRb(indiceRb *valor, rb* raiz);

void ajustar_remocao(rb* raiz, rb filho, rb pai);

void removerRb(rb* raiz, int chave);

rb buscar(rb raiz, int chave);

/*

rb delete_node(rb root, int key);
int is_red(rb node);
rb rotate_left(rb node);
rb rotate_right(rb node);
void flip_colors(rb node);
rb find_min(rb node);
*/

#endif
