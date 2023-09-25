 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livraria.h"

void inicializarBst(bst *raiz){
	*raiz = NULL;
}

void inicializarAvl(avl *raiz){
	*raiz = NULL;
}

void inicializarRb(rb *raiz){
	*raiz = NULL;
}

// ----------------- A R Q U I V O S -----------------

int inicializarTabela(tabela *tab){
	inicializarBst(&tab->arvoreBstIndice);
	inicializarAvl(&tab->arvoreAvlIndice);
	inicializarRb(&tab->arvoreRbIndice);
	tab->arquivo = fopen("dados.dat", "a+b");
	tab->arvoreBstIndice = carregarArquivoBst("indicesBst.dat", tab->arvoreBstIndice);
	tab->arvoreAvlIndice = carregarArquivoAvl("indicesAvl.dat", tab->arvoreAvlIndice);
	tab->arvoreRbIndice = carregarArquivoRb("indicesRb.dat", tab->arvoreRbIndice);

	if(tab->arquivo != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo);
	salvarArquivoBst("indicesBst.dat", tab->arvoreBstIndice);
	salvarArquivoAvl("indicesAvl.dat", tab->arvoreAvlIndice);
	salvarArquivoRb("indicesRb.dat", tab->arvoreRbIndice);
}

void adicionarProduto(tabela *tab, produto *p){
	int posicaoNovoRegistro;

	if(tab->arquivo != NULL) {
			fseek(tab->arquivo, 0L, SEEK_END);
			posicaoNovoRegistro = ftell(tab->arquivo);

			// Adicionar BST - ID
			indiceBst *novo = (indiceBst*)malloc(sizeof(indiceBst));
			novo->chave = p->id;
			novo->indice = posicaoNovoRegistro;
			tab->arvoreBstIndice = adicionarBst(novo, tab->arvoreBstIndice);

			// Adicionar AVL - Titulo
			indiceAvl *aux = (indiceAvl*)malloc(sizeof(indiceAvl));
			strcpy(aux->chave, p->titulo);
			aux->indice = posicaoNovoRegistro;
			tab->arvoreAvlIndice = adicionarAvl(aux, tab->arvoreAvlIndice);

			// Adicionar RB - Ano de Lançamento
			indiceRb *auxRb = (indiceRb*)malloc(sizeof(indiceRb));
			auxRb->chave = p->ano;
			auxRb->indice = posicaoNovoRegistro;
			adicionarRb(auxRb, &tab->arvoreRbIndice);

			fwrite(p, sizeof(produto), 1, tab->arquivo);	

			int tam = strlen(p->titulo) + 1;
			fwrite(&tam, sizeof(tam), 1, tab->arquivo);
			fwrite(p->titulo, sizeof(char), tam, tab->arquivo);

	}
}

void removerProduto(tabela *tab, int id){

	produto *p = procurarLivroBst(tab, id);	
	if(p == NULL){
		return;
	}else{
		tab->arvoreBstIndice = removerBst(p->id, tab->arvoreBstIndice);
		tab->arvoreAvlIndice = removerAvl(tab->arvoreAvlIndice, p->titulo);
		removerRb(&tab->arvoreRbIndice, p->ano);
	}
}

produto *ler_dados() {
	produto *novo = (produto*) malloc(sizeof(produto));
	char * buffer = (char *) malloc(256*sizeof(char));
	
	system("clear");
	printf("┌-----------------------------┐\n");
	printf("|         Livraria BIG        |\n");
	printf("└-----------------------------┘\n");
	printf("┌-----------------------------┐\n");
	getchar();
	printf("| Titulo: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->titulo = (char *) malloc ((strlen(buffer)+1) * sizeof(char));
	strcpy(novo->titulo, buffer);
	
	printf("| Autor(a): ");
	fgets(novo->autor, 20,  stdin);
	tirar_enter(novo->autor);
	
	printf("| Preco: ");
	scanf("%f", &novo->preco);

	printf("| Ano de Lancamento: ");
	scanf("%d", &novo->ano);

	printf("| ID: ");
	scanf("%d", &novo->id);
	printf("└-----------------------------┘\n");
	free(buffer);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}


// ------------ B S T ------------ 

produto *procurarLivroBst(tabela *tab, int chave) {
    if(tab->arquivo != NULL) {
    no_bst *temp;
    temp = tab->arvoreBstIndice;
    while(temp!=NULL){
        if(temp->dado->chave == chave) {

		fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

		produto * encontrado = (produto*) malloc(sizeof(produto));
		fread(encontrado, sizeof(produto), 1, tab->arquivo);
		
		int tam;
		fread(&tam, sizeof(int),1, tab->arquivo);
		encontrado->titulo = (char*)malloc(tam*sizeof(char));
		fread(encontrado->titulo, sizeof(char),tam, tab->arquivo);
		
		printf("┌----------------------------------------------------------------------------------┐\n");
		printf("| ID: %d, Autor: %s, Titulo: %s, Preco: %.2f, Ano de Lancamento: %d\n", encontrado->id, encontrado->autor, encontrado->titulo, encontrado->preco, encontrado->ano);
		printf("└----------------------------------------------------------------------------------┘\n");
        return encontrado;

        } else {

        if(chave > temp->dado->chave)
            temp = temp->dir;
        else
            temp = temp->esq;                
    		}
    	}
    }
    	printf("┌-----------------------------┐\n");
	printf("|      ID Nao Encontrado      |\n");
	printf("└-----------------------------┘\n\n");
    return NULL;
}

void imprimirBst(bst raiz, tabela * tab) {
	produto * temp = (produto *) malloc (sizeof(produto));
	printf("┌----------------------------------------------------------------------------┐\n");
	if (!temp) {
		printf("Erro: falha ao alocar memória.\n");
		return;
	}
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}
		if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}

	int tam;
	fread(&tam, sizeof(int),1, tab->arquivo);
	temp->titulo = (char*)malloc(tam);
	fread(temp->titulo, sizeof(char),tam, tab->arquivo);
	
	
	printf("| ID: %d, Autor: %s, Titulo: %s, Preco: %.2f, Ano: %d\n", raiz->dado->chave,temp->autor, temp->titulo, temp->preco, temp->ano);
	free(temp);
	printf("└----------------------------------------------------------------------------┘\n");
}

void inOrderBst(bst raiz, tabela* tab) {
	if(tab->arvoreBstIndice == NULL){

		printf("┌-------------------------┐\n");
		printf("|       Arvore Vazia      |\n");
		printf("└-------------------------┘\n");
	
		return;
	}
	if(raiz != NULL) {
		inOrderBst(raiz->esq, tab);
		imprimirBst(raiz, tab);
		inOrderBst(raiz->dir, tab);
	}
	
}


// ------------ R B ------------ 

produto *procurarLivroRb(tabela *tab, int chave) {
    if(tab->arquivo != NULL) {
    no_rb *temp;
    temp = tab->arvoreRbIndice;
    while(temp!=NULL){
        if(temp->dado->chave == chave) {

		fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

		produto * encontrado = (produto*) malloc(sizeof(produto));
		fread(encontrado, sizeof(produto), 1, tab->arquivo);
		
		int tam;
		fread(&tam, sizeof(int),1, tab->arquivo);
		encontrado->titulo = (char*)malloc(tam*sizeof(char));
		fread(encontrado->titulo, sizeof(char),tam, tab->arquivo);
		
		printf("┌----------------------------------------------------------------------------------┐\n");
		printf("| ID: %d, Autor: %s, Titulo: %s, Preco: %.2f, Ano de Lancamento: %d\n", encontrado->id, encontrado->autor, encontrado->titulo, encontrado->preco, encontrado->ano);
		printf("└----------------------------------------------------------------------------------┘\n");
        return encontrado;
        } else {
        if(chave > temp->dado->chave)
            temp = temp->dir;
        else
            temp = temp->esq;                
	    	}
	    }
    }
   	printf("┌------------------------------┐\n");
	printf("|       Ano Nao Encontrado     |\n");
	printf("└------------------------------┘\n\n");
    return NULL;
}

void buscarRb(int chave, rb raiz, tabela *tab){
    if(raiz != NULL) {
        buscarRb(chave,raiz->esq, tab);
        if(chave == raiz->dado->chave){
            imprimirRb(raiz, tab);
        }
        buscarRb(chave,raiz->dir, tab);
    }
    else if(tab->arvoreRbIndice == NULL){
    		printf("┌------------------------------┐\n");
		printf("|       Ano Nao Encontrado     |\n");
		printf("└------------------------------┘\n\n");
	    return;
    }
}

void imprimirRb(rb raiz, tabela * tab) {
	produto *temp = (produto*) malloc(sizeof(produto));
	printf("┌----------------------------------------------------------------------------┐\n");
	if (!temp) {
		printf("Erro: falha ao alocar memória.\n");
		return;
	}
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}
		if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}

	int tam;
	fread(&tam, sizeof(int),1, tab->arquivo);
	temp->titulo = (char*)malloc(tam);
	fread(temp->titulo, sizeof(char),tam, tab->arquivo);
	
	printf("| Ano: %d, Autor: %s, Titulo: %s, Preco: %.2f, ID: %d\n",raiz->dado->chave, temp->autor, temp->titulo, temp->preco, temp->id);
	free(temp);
	printf("└----------------------------------------------------------------------------┘\n");
}


void inOrderRb(rb raiz, tabela* tab) {

	if(tab->arvoreRbIndice == NULL){
		printf("┌-------------------------┐\n");
		printf("|       Arvore Vazia      |\n");
		printf("└-------------------------┘\n");
	
		return;
	}

	else if(raiz != NULL) {
		inOrderRb(raiz->esq, tab);
		imprimirRb(raiz, tab);
		inOrderRb(raiz->dir, tab);
	}
}

// ------------ A V L ------------ 

produto* procurarLivroAvl(tabela *tab, char* chave) {
    if(tab->arquivo != NULL){
    no_avl *temp;
    temp = tab->arvoreAvlIndice;
    while(temp!=NULL){
        if(strcmp(temp->dado->chave,chave) == 0) {
            fseek(tab->arquivo, temp->dado->indice, SEEK_SET);
			produto* encontrado = (produto*) malloc(sizeof(produto));
			
            fread(encontrado, sizeof(produto), 1, tab->arquivo);

            int tam;
			fread(&tam, sizeof(int),1, tab->arquivo);
			encontrado->titulo = (char*)malloc(tam*sizeof(char));
			fread(encontrado->titulo, sizeof(char),tam, tab->arquivo);

            		printf("┌----------------------------------------------------------------------------------┐\n");
			printf("| ID: %d, Autor: %s, Titulo: %s, Preco: %.2f, Ano de Lancamento: %d\n", encontrado->id, encontrado->autor, encontrado->titulo, encontrado->preco, encontrado->ano);
			printf("└----------------------------------------------------------------------------------┘\n");
			return encontrado;
        	}else{
	            if(strcmp(chave, temp->dado->chave) > 0)
	                temp = temp->dir;
	            else
	                temp = temp->esq;                
	        }
    	}
    }
    	printf("┌---------------------------------┐\n");
	printf("|       Titulo Nao Encontrado     |\n");
	printf("└---------------------------------┘\n\n");
    return NULL;
}

void imprimirAvl(avl raiz, tabela * tab) {
	produto *temp = (produto*) malloc(sizeof(produto));
	printf("┌----------------------------------------------------------------------------┐\n");
	if (!temp) {
		printf("Erro: falha ao alocar memória.\n");
		return;
	}
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}
		if (fread(temp, sizeof(produto), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}
	
	printf("| Titulo: %s, Autor: %s, Preco: %.2f, Ano: %d, ID: %d\n",raiz->dado->chave, temp->autor, temp->preco, temp->ano, temp->id);
	free(temp);
	printf("└----------------------------------------------------------------------------┘\n");
}

void inOrderAvl(avl raiz, tabela* tab) {
	if(tab->arvoreAvlIndice == NULL){
		printf("┌-------------------------┐\n");
		printf("|       Arvore Vazia      |\n");
		printf("└-------------------------┘\n");
	
		return;
	}
	else if(raiz != NULL) {
		inOrderAvl(raiz->esq, tab);
		imprimirAvl(raiz, tab);
		inOrderAvl(raiz->dir, tab);
	}
}



// ------------ S A L V A R - B S T ------------ 

void salvarArquivoBst(char *nome, bst a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvarAuxiliarBst(a, arq);
		fclose(arq);
	}
}

void salvarAuxiliarBst(bst raiz, FILE *arq){
	if(raiz != NULL) {		
		fwrite(raiz->dado, sizeof(indiceBst), 1, arq);
		salvarAuxiliarBst(raiz->esq, arq);
		salvarAuxiliarBst(raiz->dir, arq);
	}
}

bst carregarArquivoBst(char *nome, bst a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	indiceBst * temp;
	if(arq != NULL) {
		temp = (indiceBst*) malloc(sizeof(indiceBst));
		while(fread(temp, sizeof(indiceBst), 1, arq)) {
			
			a = adicionarBst(temp, a);			
			temp = (indiceBst*) malloc(sizeof(indiceBst));

		}
		fclose(arq);
	}
	return a;
}

// ------------ S A L V A R - A V L ------------

void salvarArquivoAvl(char *nome, avl a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvarAuxiliarAvl(a, arq);
		fclose(arq);
	}
}

void salvarAuxiliarAvl(avl raiz, FILE *arq){
	if(raiz != NULL) {		
		fwrite(raiz->dado, sizeof(indiceAvl), 1, arq);
		salvarAuxiliarAvl(raiz->esq, arq);
		salvarAuxiliarAvl(raiz->dir, arq);
	}
}

avl carregarArquivoAvl(char *nome, avl a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	indiceAvl * temp;
	if(arq != NULL) {
		temp = (indiceAvl*) malloc(sizeof(indiceAvl));
		while(fread(temp, sizeof(indiceAvl), 1, arq)) {
			
			a = adicionarAvl(temp, a);			
			temp = (indiceAvl*) malloc(sizeof(indiceAvl));

		}
		fclose(arq);
	}
	return a;
}

// ------------ S A L V A R - R B ------------ //

void salvarArquivoRb(char *nome, rb a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvarAuxiliarRb(a, arq);
		fclose(arq);
	}
}

void salvarAuxiliarRb(rb raiz, FILE *arq){
	if(raiz != NULL) {		
		fwrite(raiz->dado, sizeof(indiceRb), 1, arq);
		salvarAuxiliarRb(raiz->esq, arq);
		salvarAuxiliarRb(raiz->dir, arq);
	}
}

rb carregarArquivoRb(char *nome, rb a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	indiceRb * temp;
	if(arq != NULL) {
		temp = (indiceRb*) malloc(sizeof(indiceRb));
		while(fread(temp, sizeof(indiceRb), 1, arq)) {
			
			adicionarRb(temp, &a);			
			temp = (indiceRb*) malloc(sizeof(indiceRb));

		}
		fclose(arq);
	}
	return a;
}
