#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int cod;
	struct Item* ant;
	struct Item* prox;
}Item;

typedef struct Pilha{
	int qtd;
	struct Item* start;
}Pilha;

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void delItem(Pilha* lst){
	system("clear");
	
	if(!lst->start){
		printf("Lista Vázia!");
		wait();
		return;
	}
	int c;
	printf("Escreva o código: ");
	scanf(" %d", &c);
	
	Item* a= lst->start;
	
	while(a){
		if(c==a->cod){
			if(a->ant==NULL){
				lst->start=a->prox;
				
				if(a->prox) a->prox->ant=NULL;
			} else{
				a->ant->prox=a->prox;
				a->prox->ant=a->ant;
			}
			free(a);
			printf("Código deletado!");
			wait();
			return;
		}
		a=a->prox;
	}
	printf("Não encontrado!");
	wait();
}

void listarItem(Pilha* lst){
	system("clear");
	
	if(!lst->start){
		printf("Lista vázia!");
		wait();
		return;
	}
	Item* a=lst->start;
	
	while(a){
		printf("Código: %d\n\n", a->cod);
		a=a->prox;
	}
	wait();
}

void cadastrarItem(Pilha* lst){
	system("clear");
	
	Item* a=malloc(sizeof(Item));
	
	printf("Código: ");
	scanf(" %d", &a->cod);
	
	a->prox=lst->start;
	a->ant=NULL;
	
	if(lst->start) lst->start->ant=a;
	
	lst->start=a;
	lst->qtd++;
}

int interface(){
	system("clear");
	
	printf("=========================MENU============================\n\n");
	printf("	1- Cadastrar\n");
	printf("	2- Listar\n");
	printf("	3- Excluir\n");
	printf("	0- Sair\n");
	int op;
	scanf(" %d", &op);
	
	return op;
}

int main(){
	Pilha* a=malloc(sizeof(Pilha));
	
	do{
		switch(interface()){
			case 1: cadastrarItem(a);
					break;
			case 2: listarItem(a);
					break;
			case 3: delItem(a);
					break;
			case 0: printf("Finalizando o Programa...");
					wait();
					return 0;
			default: printf("Valor inexistente! Tente Novamente.");
					 wait();
					 break;
		}
	}while(1);
}
