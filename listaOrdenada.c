#include "listaOrdenada.h"
#include <stdlib.h>

//inicializa a lista e atribui a funcao de comparacao escolhida
void inicializa( lista* l, int (*menor_igual_maior)( item i1, item i2)){
	node *n = malloc(sizeof(node));
	n->data = NULL;
	n->next = n->prev = l->sentinela = n;
	l->quantidade = 0;
	l->comp = (*menor_igual_maior);
}

//desaloca a lista
void destroi(lista* l){
	while(!vazia(l)){
		node *n = l->sentinela->prev;

		n->next->prev = n->prev;
		n->prev->next = n->next;
		free(n);
		l->quantidade--;
		
	}

	free(l->sentinela);
}

//verifica se a lista esta vazia
int vazia(lista* l){
	return l->sentinela->next == l->sentinela;
}

//insere o elemento já ordenado a partir da funcao de comparacao
//passada na inicializacao da lista
void insere(lista* l, item i){
	node *n = malloc(sizeof(node));
	n->data = i;

	node *noit = l->sentinela->next; //iterador de nos
	while(1){
		if(l->comp(noit->data,i) >= 0 || noit == l->sentinela){
			n->next = noit;
			n->prev = noit->prev;
			noit->prev->next = n;
			noit->prev = n;
			l->quantidade++;
			return;	
		} 
		noit = noit->next;
	}
}

//remove o primeiro elemento igual a i encontrado na lista
void retiraUm(lista* l, item i){

	iterador it = primeiro(l);

	node *deletado;
	while(!acabou(it)){
		if(elemento(it) == i){
			deletado = it.posicao;
			deletado->prev->next = deletado->next;
			deletado->next->prev = deletado->prev;
			free(deletado);
			l->quantidade--;
			return;
		}

		proximo(&it);
	}
}

//remove todos os elementos iguais a i encontrados na lista
void retira(lista* l, item i){

	iterador it = primeiro(l);

	node *deletado;
	while(!acabou(it) && elemento(it) <= i){
		if(elemento(it) == i){
			deletado = it.posicao;
			it.posicao = deletado->next;
			deletado->prev->next = deletado->next;
			deletado->next->prev = deletado->prev;
			free(deletado);
			l->quantidade--;
		}
		else proximo(&it);
	}

}

//retorna um iterador para o primeiro elemento da lista
iterador primeiro(lista* l){
	iterador it;
	it.posicao = l->sentinela->next;
	it.estrutura = l;
	return it;
}

//retorna um iterador para o ultimo elemento da lista
iterador ultimo(lista* l){
	iterador it;
	it.posicao = l->sentinela->prev;
	it.estrutura = l;
	return it;
}

int elementov(iterador it, item* i){
	if( !acabou( it ) ) {
		*i = it.posicao->data;
		return 1;
	}
	return 0;
}

//retorna o valor da posicao de um determinado iterador
item elemento(iterador it){
	return it.posicao->data;
}

//passa o iterador para o proximo elemento da lista
int proximo(iterador* it){
	if( !acabou( *it ) ) {
		it->posicao = it->posicao->next;
		return 1;
	}
	return 0;
}

//retorna o iterador para o elemento anterior da lista
int anterior(iterador* it){
	if( !acabou( *it ) ) {
		it->posicao = it->posicao->prev;
		return 1;
	}
	return 0;
}

//verifica se o iterador retornou para a sentinela
int acabou(iterador it){
	return it.posicao == it.estrutura->sentinela;
}


