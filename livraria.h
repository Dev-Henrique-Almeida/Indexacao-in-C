#ifndef LIVRARIA_H
#define LIVRARIA_H
#include "./bst/bst.c"
#include "./bst/bst.h"
#include "./avl/avl.c"
#include "./avl/avl.h"
#include "./rb/rb.c"
#include "./rb/rb.h"


typedef struct livro{
	int id;
	char autor[61];
	char *titulo;
	float preco;
	int ano;
}produto;


// ----------------- A V L -----------------



typedef struct tabela {
	FILE *arquivo;
	bst arvoreBstIndice;
	avl arvoreAvlIndice;
	rb arvoreRbIndice;
} tabela;



// Inicialização
int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarProduto(tabela *tab, produto *p);
void removerProduto(tabela *tab, int id);

produto *ler_dados();
void tirar_enter(char *string);

// Procurar BST, AVL e RB
produto *procurarLivroBst(tabela *tab, int chave);
produto *procurarLivroAvl(tabela *tab, char *chave); 
produto *procurarLivroRb(tabela *tab, int chave); 
void buscarRb(int chave, rb raiz, tabela *tab);


// Imprimir BST, AVL e RB
void imprimirBst(bst raiz, tabela * tab);
void inOrderBst(bst raiz, tabela* tab);

void imprimirAvl(avl raiz, tabela * tab);
void inOrderAvl(avl raiz, tabela* tab);

void imprimirRb(rb raiz, tabela* tab);
void inOrderRb(rb raiz, tabela* tab);



// Salvar e Carregar, BST, AVL e RB
void salvarArquivoBst(char *nome, bst a);
void salvarAuxiliarBst(bst raiz, FILE *arq);
bst carregarArquivoBst(char *nome, bst a);

void salvarArquivoAvl(char *nome, avl a);
void salvarAuxiliarAvl(avl raiz, FILE *arq);
avl carregarArquivoAvl(char *nome, avl a);

void salvarArquivoRb(char *nome, rb a);
void salvarAuxiliarRb(rb raiz, FILE *arq);
rb carregarArquivoRb(char *nome, rb a);

#endif
