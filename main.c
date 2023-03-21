#include <stdio.h>
#include <stdlib.h>
#include "livraria.h"
#include "livraria.c"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao, valor;
	inicializarTabela(&tab);

	system("clear");
	while(1) {
		printf("┌------------------------┐\n");
		printf("|      Livraria BIG      |\n");
		printf("└------------------------┘\n");
		printf("┌------------------------┐\n");
		printf("| 1 - Adicionar          |\n");
		printf("| 2 - Procurar           |\n");
		printf("| 3 - Remover            |\n");
		printf("| 4 - Em Ordem           |\n");
		printf("| 5 - Limpar tela        |\n");
		printf("| 99 - Sair              |\n");
		printf("└------------------------┘\n");
		scanf("%d", &opcao);



		switch(opcao) {
								
				case 1:
						adicionarProduto(&tab, ler_dados());
						break;
				case 2:
						system("clear");
						printf("┌--------------------------┐\n");
						printf("|      Livraria BIG        |\n");
						printf("└--------------------------┘\n");
						printf("┌--------------------------┐\n");
						printf("| 1 - Procurar (ID)        |\n");
						printf("| 2 - Procurar (Titulo)    |\n");
						printf("| 3 - Procurar (Ano)       |\n");
						printf("└--------------------------┘\n");
						scanf("%d", &opcao);
						switch(opcao){
							case 1:
								system("clear");
								printf("┌------------------------┐\n");
								printf("|      Livraria BIG      |\n");
								printf("└------------------------┘\n");
								printf("\nInforme o número de ID que deseja buscar: ");
								scanf("%d", &valor);
								produto *p = procurarLivroBst(&tab, valor);
								break;
							case 2:
								system("clear");
								printf("┌------------------------┐\n");
								printf("|      Livraria BIG      |\n");
								printf("└------------------------┘\n");
								printf("\nInforme o nome do titulo que deseja buscar: ");
								while(getchar() != '\n');
		                        char titulo[200];
		                        fgets(titulo, 200, stdin);
		                        titulo[strcspn(titulo, "\n")] = 0;
								p = procurarLivroAvl(&tab, titulo);
								break;
							case 3:
								system("clear");
								printf("┌------------------------┐\n");
								printf("|      Livraria BIG      |\n");
								printf("└------------------------┘\n");
								printf("\nInforme o ano de lancamento que deseja buscar: ");
								scanf("%d", &valor);
								buscarRb(valor, tab.arvoreRbIndice, &tab);
								break;

						}
						
						break;
				case 3:
						system("clear");
						printf("┌------------------------┐\n");
						printf("|      Livraria BIG      |\n");
						printf("└------------------------┘\n");
						printf("\nInforme o número de ID que deseja remover: ");
						scanf("%d", &valor);
						removerProduto(&tab, valor);
						break;
				case 4:
						system("clear");
						printf("┌------------------------┐\n");
						printf("|      Livraria BIG      |\n");
						printf("└------------------------┘\n");
						printf("\nInOrder da Árvore BST - (ID):\n");
						inOrderBst(tab.arvoreBstIndice, &tab);
						printf("\n");
						printf("\nInOrder da Árvore AVL - (Titulo):\n");
						inOrderAvl(tab.arvoreAvlIndice, &tab);
						printf("\n");
						printf("\nInOrder da Árvore RB - (Ano de Lancamento):\n");
						inOrderRb(tab.arvoreRbIndice, &tab);
						printf("\n");
						break;
				case 5:
						system("clear");
						break;
				case 99:
						system("clear");
						printf("┌-------------------------------------┐\n");
						printf("|             Livraria BIG            |\n");
						printf("└-------------------------------------┘\n");
						printf("┌-------------------------------------┐\n");
						printf("|      Henrique de Almeida Silva      |\n");
						printf("|      3º Periodo - BCC   19/03/2023  |\n");
						printf("└-------------------------------------┘\n");
						finalizar(&tab);
						exit(0);
		}
	}
}
