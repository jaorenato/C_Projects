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

void cadastrarItem(Pilha* lst){
	system("clear");
	Item* a=malloc(sizeof(Item));
	
	printf("Código: ");
	scanf(" %d", &a->cod);
	
	if(!lst->start){
		a->ant=a;
		a->prox=a;
		lst->start=a;
		lst->qtd++;
		return;
	}
	if(a->cod < lst->start->cod){
		Item* fim=lst->start->ant;
		
		a->prox=fim;
		a->ant=lst->start;
		fim->prox=a;
		lst->start->ant=a;
		lst->start=a;
		lst->qtd++;
		return;
	}
	Item* atual=lst->start;
	
	do{
		if(atual->prox==lst->start || a->cod < atual->prox->cod){
			Item* prox= atual->prox;
			
			a->prox=prox;
			a->ant=atual;
			prox->ant=a;
			atual->prox=a;
			lst->qtd++;
			return;
		}
		atual=atual->prox;
	}while(atual!=lst->start);
}

void listarItem(Pilha* lst){
	system("clear");
	
	if(!lst->start){
		printf("Lista vázia!");
		wait();
		return;
	}
	Item* a=lst->start;
	
	do{
		printf("Código: %d\n\n", a->cod);
		a=a->prox;
	}while(a!=lst->start);
	wait();
}

void delItem(Pilha* lst){
	system("clear");
	
	if(!lst->start){
		printf("Lista vázia!");
		wait();
		return;
	}
	int c;
	printf("Digite o código: ");
	scanf(" %d", &c);
	
	Item* a=lst->start;
	do{
		if(a->cod==c){
			if(a->ant==a && a->prox==a){
				free(a);
				lst->start=NULL;
			} else{
				a->ant->prox=a->prox;
				a->prox->ant=a->ant;
				
				if(a==lst->start) lst->start=a->prox;
				free(a);
			}
			lst->qtd--;
			printf("Código excluido!");
			wait();
			return;
		}
		a=a->prox;
	}while(a!=lst->start);
	printf("Código não encontrado!");
	wait();
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
