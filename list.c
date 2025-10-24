#include <stdio.h>
#include <stdlib.h>

typedef struct Produto{
	char descricao[100];
	float preco;
	int codigo;
	struct Produto *prox;
}Produto; 

int interface(){
	system("clear");
	
	printf("	1- Enfileirar Produto\n");
	printf("	2- Remover Produto\n");
	printf("	3- Listar Produtos\n");
	int op;
	scanf(" %d", &op);
	
	return op;
}

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

Produto* setProduto(Produto* f){
	Produto* new= malloc(sizeof(Produto));
	
	printf("Informe as características do produto: ");
	scanf(" %[^\n]s", new->descricao);
	printf("Informe o valor produto: ");
	scanf(" %f", &new->preco); 
	printf("Informe o ID do produto: ");
	scanf(" %d", &new->codigo);
	
	if(f) f->prox=new;
	new->prox=NULL;
	
	return new;
}

void getProduto(Produto* i){
	system("clear");
		while(i){
			printf("Descrição: %s\nValor: %.2f\nCódigo: %d\n", i->descricao, i->preco, i->codigo);
			printf("----------------------------\n");
			i=i->prox;
		}
	wait();
}

Produto* removerProduto(Produto* i){
	system("clear");
	if(!i){
		printf("Não há elementos para ser removidos!\n");
		wait();
		return i;
	}

	Produto* alvo=i;
	Produto* newInicio= i->prox;
	
	printf("Deseja realmente retirar o produto %d? [s/n]\n", alvo->codigo);
	char r;
	scanf(" %c", &r);
	if(r=='s'){
		free(alvo);
		return newInicio;
	}
	return i;
}

int main(){
	Produto* inicio=NULL;
	Produto* fim=NULL;
	
	do{
		switch(interface()){
			case 1: fim=setProduto(fim);
					if(!inicio) inicio=fim;
					break;
			case 2: inicio=removerProduto(inicio);
					if(!inicio) fim=NULL;
					break;
			case 3: getProduto(inicio);
					break;
			default: return 0;
		}
	}while(1);
}
