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
	
	printf("	1- Empilhar Produto\n");
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

Produto* pushProduto(Produto* a){
	Produto* new= malloc(sizeof(Produto));
	
	printf("Informe as características do produto: ");
	scanf(" %[^\n]s", new->descricao);
	printf("Informe o valor produto: ");
	scanf(" %f", &new->preco); 
	printf("Informe o ID do produto: ");
	scanf(" %d", &new->codigo);
	
	new->prox=a;
	
	return new;
}

void getProduto(Produto* a){
	system("clear");
		while(a){
			printf("Descrição: %s\nValor: %.2f\nCódigo: %d\n", a->descricao, a->preco, a->codigo);
			printf("----------------------------\n");
			a=a->prox;
		}
	wait();
}

Produto* popProduto(Produto* a){
	system("clear");
	Produto* atual=a;
	
	printf("Deseja realmente retirar o produto %d? [s/n]\n", a->codigo);
	char r;
	scanf(" %c", &r);
	if(r=='s'){
		atual=a->prox;
		free(a);
	}
	return atual;
}

int main(){
	Produto* a=NULL;
	do{
		switch(interface()){
			case 1: a=pushProduto(a);
					break;
			case 2: a=popProduto(a);
					break;
			case 3: getProduto(a);
					break;
			default: return 0;
		}
	}while(1);
}

