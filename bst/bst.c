#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

bst adicionarBst(indiceBst *valor, bst raiz){
	if (raiz == NULL){
        bst novo = (bst)malloc(sizeof(struct no_bst));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (raiz->dado->chave < valor->chave)
    {
       raiz->dir = adicionarBst(valor, raiz->dir);
    }else{
      raiz->esq = adicionarBst(valor, raiz->esq);
    }
    return raiz;
}



int altura(bst raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}




indiceBst *maiorElementoBst(bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maiorElementoBst(raiz->dir);
}



bst removerBst (int valor, bst raiz) {
	if(raiz == NULL){ 
		return NULL;
	}
	
	else if(raiz->dado->chave == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maiorElementoBst(raiz->esq);
		raiz->esq = removerBst(raiz->dado->chave, raiz->esq);
		return raiz;
	}	
	else if(valor > raiz->dado->chave) {
			raiz->dir = removerBst(valor, raiz->dir);
	} else {
			raiz->esq = removerBst(valor, raiz->esq);
	}
	return raiz;
}

