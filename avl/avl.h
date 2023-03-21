#ifndef AVL_H
#define AVL_H

typedef struct indiceAvl {
	char chave[61];
	int indice;
} indiceAvl;

typedef struct no_avl
{
    indiceAvl *dado;
    struct no_avl *esq, *dir;
    int altura;
}no_avl;

typedef no_avl *avl;


void inicializarAvl(avl *raiz);
avl maiorElementoAvl(avl raiz);
int alturaNo(avl no);
int fatorBalanceamento(avl no);
avl RotacaoEsquerda(avl raiz);
avl RotacaoDireita(avl raiz);
avl RotacaoDuplaEsquerda(avl raiz);
avl RotacaoDuplaDireita(avl raiz);
avl balancear(avl raiz);
avl adicionarAvl(indiceAvl *valor, avl raiz);
avl removerAvl(avl raiz, char *valor);


#endif

