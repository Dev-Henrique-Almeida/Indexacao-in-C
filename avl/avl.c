#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include <string.h>
avl maiorElementoAvl (avl raiz){
    avl aux = raiz;
    while(aux != NULL){
        aux = aux->dir;
    }
    return aux;
}

int alturaNo(avl no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

int fatorBalanceamento(avl no){
    if(no != NULL){
        return (alturaNo(no->esq) - alturaNo(no->dir));
    }else{
        return 0;
    }
}

avl RotacaoEsquerda(avl raiz){
    avl y,f;

    y = raiz->dir;
    f = y->esq;

    y->esq = raiz;
    raiz->dir = f;

    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    y->altura = maior(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

avl RotacaoDireita(avl raiz){
    avl y,f;

    y = raiz->esq;
    f = y->dir;

    y->dir = raiz;
    raiz->esq = f;

    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    y->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;

    return y;
}

avl RotacaoDuplaEsquerda(avl raiz){
    raiz->dir = RotacaoDireita(raiz->dir);
    return RotacaoEsquerda(raiz);
}

avl RotacaoDuplaDireita(avl raiz){
    raiz->esq = RotacaoEsquerda(raiz->esq);
    return RotacaoDireita(raiz);
}

avl balancear(avl raiz){

    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0){
        raiz = RotacaoEsquerda(raiz);
    }

    else if(fb > 1 && fatorBalanceamento(raiz->esq) >= 0){
        raiz = RotacaoDireita(raiz);
    }

    else if(fb > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz = RotacaoDuplaDireita(raiz);
    }

    else if(fb < -1 && fatorBalanceamento(raiz->dir) < 0){
        raiz = RotacaoDuplaEsquerda(raiz);
    }
    
    return raiz;
}

avl adicionarAvl(indiceAvl *valor, avl raiz){
    if (raiz == NULL)
    {
        avl novo = (avl)malloc(sizeof(struct no_avl));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }else{
        if(strcmp(valor->chave, raiz->dado->chave) > 0){
        	//printf("Direita:\n raiz: %s \n valor: %s", raiz->dado->chave, valor->chave);
           raiz->dir = adicionarAvl(valor, raiz->dir);
        }else{
        	//printf("Esquerda:\n raiz: %s \n valor: %s", raiz->dado->chave, valor->chave);
          raiz->esq = adicionarAvl(valor, raiz->esq);
        }
    }

    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    return raiz;
}

avl removerAvl(avl raiz, char* valor){
    if(raiz == NULL){
        return NULL;
    }
    else{
        if(strcmp(raiz->dado->chave, valor) == 0){
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            if(raiz->esq == NULL && raiz->dir != NULL){
                avl temp = raiz->dir;
                free(raiz);
                return temp;
            }
            if(raiz->esq != NULL && raiz->dir == NULL){
                avl temp = raiz->esq;
                free(raiz);
                return temp;
            }
            avl temp = maiorElementoAvl(raiz->esq);
            strcpy(raiz->dado->chave, temp->dado->chave); //raiz->valor = temp->valor;
            strcpy(temp->dado->chave, valor); //temp->valor = valor;
            raiz->esq = removerAvl(raiz->esq, valor);
            return raiz;
        }
        else{
            if(strcmp(raiz->dado->chave,valor) > 0){
                raiz->esq = removerAvl(raiz->esq, valor);
            }
            else{
                raiz->dir = removerAvl(raiz->dir, valor);
            }
        }
    }
    
    raiz->altura = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz = balancear(raiz);
    return raiz;
    }

