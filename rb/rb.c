#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

rb criar_no(indiceRb *info){
   rb novo = (rb)malloc(sizeof(struct no_rb));
   novo->dado = info;
   novo->pai = NULL;
   novo->esq = NULL;
   novo->dir = NULL;
   novo->c = VERMELHO;
   return novo;
}

int cor(rb no) {
   if(no == NULL || no->c == PRETO)
   return 1;
   else
   return 0;
}

int eh_esquerdo(rb no) {
   if(no == no->pai->esq)
   return 1;
   else
   return 0;
}

int eh_raiz(rb no) {
   if(no->pai == NULL)
   return 1;
   else
   return 0;
}

rb tio (rb n) {
   if(eh_esquerdo(n->pai))
   return n->pai->pai->dir;
   else
   return n->pai->pai->esq;
}

void rotacao_simples_dir(rb *raiz, rb no, int simples){
   rb p, t;

   p = no->esq;
   t = p->dir;

   no->esq = t;
   p->dir = no;

   if(simples){
      p->c = PRETO;
      no->c = VERMELHO;
   }

   if(t != NULL)
   t->pai = no;

   p->pai = no->pai;

   if(eh_raiz(no)){
      *raiz = p;
   } else {
      if(eh_esquerdo(no)){
         no->pai->esq = p;
      } else {
         no->pai->dir = p;
      }
   }
   no->pai = p;
}

void rotacao_simples_esq(rb* raiz, rb no, int simples){
   rb p, t;

   p = no->dir;
   t = p->esq;

   no->dir = t;
   p->esq = no;

   if(simples){
      p->c = PRETO;
      no->c = VERMELHO;
   }

   if(t != NULL){
      t->pai = no;
   }

   p->pai = no->pai;

   if(eh_raiz(no)){
      *raiz = p;
   } else {
      if(eh_esquerdo(no)){
         no->pai->esq = p;
      } else {
         no->pai->dir = p;
      }
   }
   no->pai = p;

}

void rotacao_dupla_esq(rb* raiz, rb no){
   rotacao_simples_dir(raiz, no->dir, 0);
   rotacao_simples_esq(raiz, no, 0);

   no->pai->c = PRETO;
   no->c = VERMELHO;
}

void rotacao_dupla_dir(rb* raiz, rb no){
   rotacao_simples_esq(raiz, no->esq, 0);
   rotacao_simples_dir(raiz, no, 0);

   no->pai->c = PRETO;
   no->c = VERMELHO;
}

void ajustar(rb* raiz, rb no){
   if(eh_raiz(no)){
      no->c = PRETO;
      return;
   } else if(no->pai->c == VERMELHO){
      if(cor(tio(no)) == VERMELHO){ //CASO 1: TIO VERMELHO, BAIXA O PRETO DO AVO
         no->pai->c = PRETO;
         tio(no)->c = PRETO;
         no->pai->pai->c = VERMELHO;
         ajustar(raiz, no->pai->pai);
      } else { //CASO 2: TIO PRETO
         if(eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS ESQUERDOS
            rotacao_simples_dir(raiz, no->pai->pai, 1);

         } else if(!eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO E NO PAI, FILHOS DIREITOS
            rotacao_simples_esq(raiz, no->pai->pai, 1);

         } else if(eh_esquerdo(no) && !eh_esquerdo(no->pai)){ //NO FILHO ESQ, PAI DIR
            rotacao_dupla_esq(raiz, no->pai->pai);

         } else if(!eh_esquerdo(no) && eh_esquerdo(no->pai)){ //NO FILHO DIR, PAI ESQ;
            rotacao_dupla_dir(raiz, no->pai->pai);
         }
      }
   }
}

void adicionarRb(indiceRb *valor, rb* raiz){ //inserir funciona perfeitamente
   rb temp, pai, novo;
   temp  = *raiz;
   pai = NULL;

   while(temp != NULL){
      pai = temp;
      if(valor->chave > temp->dado->chave){
         temp = temp->dir;
      } else {
         temp = temp->esq;
      }
   }

   novo = criar_no(valor);
   novo->pai = pai;

   if(eh_raiz(novo)){
      *raiz = novo;
   } else if(valor->chave < pai->dado->chave){
      pai->esq = novo;
   } else {
      pai->dir = novo;
   }
   ajustar(raiz, novo);
}

void ajustar_remocao(rb* raiz, rb filho, rb pai) {
    rb irmao;
    
    while ((filho == NULL || filho->c == PRETO) && filho != *raiz) {
        if (filho == pai->esq) {
            irmao = pai->dir;
            
            if (irmao->c == VERMELHO) {
                irmao->c = PRETO;
                pai->c = VERMELHO;
                rotacao_simples_esq(raiz, pai, 1);
                irmao = pai->dir;
            }
            
            if ((irmao->esq == NULL || irmao->esq->c == PRETO) &&
                (irmao->dir == NULL || irmao->dir->c == PRETO)) {
                irmao->c = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                if (irmao->dir == NULL || irmao->dir->c == PRETO) {
                    irmao->esq->c = PRETO;
                    irmao->c = VERMELHO;
                    rotacao_simples_dir(raiz, irmao, 1);
                    irmao = pai->dir;
                }
                
                irmao->c = pai->c;
                pai->c = PRETO;
                irmao->dir->c = PRETO;
                rotacao_simples_esq(raiz, pai, 1);
                filho = *raiz;
                break;
            }
        } else {
            irmao = pai->esq;
            
            if (irmao->c == VERMELHO) {
                irmao->c = PRETO;
                pai->c = VERMELHO;
                rotacao_simples_dir(raiz, pai, 1);
                irmao = pai->esq;
            }
            
            if ((irmao->dir == NULL || irmao->dir->c == PRETO) &&
                (irmao->esq == NULL || irmao->esq->c == PRETO)) {
                irmao->c = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                if (irmao->esq == NULL || irmao->esq->c == PRETO) {
                    irmao->dir->c = PRETO;
                    irmao->c = VERMELHO;
                    rotacao_simples_esq(raiz, irmao, 1);
                    irmao = pai->esq;
                }
                
                irmao->c = pai->c;
                pai->c = PRETO;
                irmao->esq->c = PRETO;
                rotacao_simples_dir(raiz, pai, 1);
                filho = *raiz;
                break;
            }
        }
    }
    
    if (filho != NULL) {
        filho->c = PRETO;
    }
}

rb buscar(rb raiz, int chave) {
    // Se a árvore está vazia ou a chave é encontrada na raiz, retorna a raiz
    if (raiz == NULL || raiz->dado->chave == chave) {
        return raiz;
    }
    else{
        // Se a chave é menor que a raiz, busca na subárvore esquerda
        if (chave < raiz->dado->chave) {
        return buscar(raiz->esq, chave);
        }
        else {
    // Caso contrário, busca na subárvore direita
        return buscar(raiz->dir, chave);
        }
    }

}

 void removerRb(rb* raiz, int chave){
    rb filho, pai, sucessor;
    rb removido;
    int cor_removido;

    removido = buscar(*raiz, chave);
    if(removido == NULL){
        return;
    }

    if(removido->esq != NULL && removido->dir != NULL){
        sucessor = removido->dir;
        while(sucessor->esq != NULL){
            sucessor = sucessor->esq;
        }
        removido->dado = sucessor->dado;
        removido = sucessor;
    }

    cor_removido = removido->c;
    if (removido->esq == NULL) {
    filho = removido->dir;
    } else {
        filho = removido->esq;
    }
    pai = removido->pai;
    if(filho != NULL){
        filho->pai = pai;
    }

    if(pai == NULL){
        *raiz = filho;
    }
    else{
        if(removido == pai->esq){
            pai->esq = filho;
        }
        else{
            pai->dir = filho;
        }
    }

    if(cor_removido == PRETO){
        ajustar_remocao(raiz, filho, pai);
    }

    free(removido);
}

/*


rb delete_node(rb root, int key) {
    if (root == NULL) {
        return root;
    }

    // Procura o nó a ser removido
    if (key < root->dado->chave) {
        root->esq = delete_node(root->esq, key);
    } else if (key > root->dado->chave) {
        root->dir = delete_node(root->dir, key);
    } else {  // Encontrou o nó a ser removido
        rb temp;
        if (root->esq == NULL) {  // Se o nó não tem filho esquerdo
            temp = root->dir;
            free(root);
            return temp;
        } else if (root->dir == NULL) {  // Se o nó não tem filho direito
            temp = root->esq;
            free(root);
            return temp;
        }
        // Se o nó tem dois filhos, encontramos o sucessor em ordem
        rb succ = find_min(root->dir);
        root->dado->chave = succ->dado->chave;
        root->dir = delete_node(root->dir, succ->dado->chave);
    }

    // Rebalanceia a árvore
    if (root == NULL) {
        return root;
    }
    if (is_red(root->dir) && !is_red(root->esq)) {
        root = rotate_left(root);
    }
    if (is_red(root->esq) && is_red(root->esq->esq)) {
        root = rotate_right(root);
    }
    if (is_red(root->esq) && is_red(root->dir)) {
        flip_colors(root);
    }

    return root;
}

int is_red(rb node) {
    if (node == NULL) {
        return 0;
    }
    return node->c == VERMELHO;
}

rb rotate_left(rb node) {
    rb x = node->dir;
    node->dir = x->esq;
    x->esq = node;
    x->c = node->c;
    node->c = VERMELHO;
    return x;
}

rb rotate_right(rb node) {
    rb x = node->esq;
    node->esq = x->dir;
    x->dir = node;
    x->c = node->c;
    node->c = VERMELHO;
    return x;
}

void flip_colors(rb node) {
    node->c = VERMELHO;
    node->esq->c = PRETO;
    node->dir->c = PRETO;
}

rb find_min(rb node) {
    while (node->esq != NULL) {
        node = node->esq;
    }
    return node;
}
*/