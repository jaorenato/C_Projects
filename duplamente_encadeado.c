#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int cod;
	struct Item* prox;
	struct Item* ant;
}Item;

typedef struct Pilha{
	int qtd;
	struct Item* inicio;
}Pilha;

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void delItem(Pilha* lst){
	system("clear");
	
	if(!lst->inicio){
		printf("Lista Vázia!");
		wait();
		return;
	}
	
	int c;
	printf("Digite o código que deseja excluir: ");
	scanf(" %d", &c);
	
	Item* a=lst->inicio;
	
	while(a){
		if(a->cod==c){
			if(a->ant==NULL){
				lst->inicio=a->prox;
				
				if(a->prox) a->prox->ant=NULL;
			} else{
				a->ant->prox=a->prox;
				a->prox->ant=a->ant;
			}
			free(a);
			printf("Excluído!!");
			wait();
			return;
		}
		a=a->prox;
	}
	printf("Valor não encontraado!");
	wait();		
}

void listarItem(Pilha* lst){
	system("clear");
	
	if(!lst->inicio){
		printf("Lista Vázia!");
		wait();
		return;
	}
	
	Item* a=lst->inicio;
	
	while(a){
		printf("Código: %d\n\n", a->cod);
		a=a->prox;
	}
	wait();
}

void cadastrarItem(Pilha* lst){
	system("clear");
	
	Item* a=malloc(sizeof(Item));
	
	printf("Digite o código do Item: ");
	scanf(" %d", &a->cod);
	
	a->prox=lst->inicio;
	a->ant=NULL;
	
	if(lst->inicio) lst->inicio->ant=a;
	
	lst->inicio=a;
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
