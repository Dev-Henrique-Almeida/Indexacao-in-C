#ifndef BST_H
#define BST_H

typedef struct indiceBst {
	int chave;
	int indice;
} indiceBst;

typedef struct no_bst{
	indiceBst *dado;
	struct no_bst *esq, *dir;
}no_bst;

typedef no_bst *bst;

void inicializarBst(bst *raiz);
bst adicionarBst(indiceBst *valor, bst raiz);
indiceBst *maiorElementoBst(bst raiz);
bst removerBst (int valor, bst raiz);
int maior(int a, int b);
int altura(bst raiz);

#endif
