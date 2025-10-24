#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int cod;
	struct Item* ant;
	struct Item* prox;
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
		printf("Lista vázia!");
		wait();
		return;
	}
	printf("Digite o código: ");
	int c;
	scanf(" %d", &c);
	
	Item* a=lst->inicio;
	
	do{
		if(a->cod==c){
			if(a->ant==a && a->prox==a){
				free(a);
				lst->inicio=NULL;
				printf("Código excluído!");
				wait();
				return;
			} else{
				a->ant->prox=a->prox;
				a->prox->ant=a->ant;
				
				if(a==lst->inicio) lst->inicio=a->prox; 
				free(a);
			}
			lst->qtd--;
			printf("Código excluido!");
			wait();
			return;
		}
		a=a->prox;
	}while(a!=lst->inicio);
	printf("Código não encontrado!");
	wait();
}

void listarItem(Pilha* lst){
	system("clear");
	
	if(!lst->inicio){
		printf("Lista vázia!");
		wait();
		return;
	}
	Item* a=lst->inicio;
	
	do{
		printf("Código: %d\n\n", a->cod);
		a=a->prox;
	}while(a!=lst->inicio);
	wait();
}

void cadastrarItem(Pilha* lst){
	system("clear");
	
	Item*  a=malloc(sizeof(Item));
	
	printf("Digite o código: ");
	scanf(" %d", &a->cod);
	
	if(!lst->inicio){
		a->ant=a;
		a->prox=a;
		lst->inicio=a;
		lst->qtd++;
		return;
	}
	Item* atual=lst->inicio;
	
	if(a->cod < lst->inicio->cod){
		Item* fim=lst->inicio->ant;
		
		a->prox=lst->inicio;
		a->ant=fim;
		fim->prox=a;
		lst->inicio->ant=a;
		lst->inicio=a;
		
		lst->qtd++;
		return;
	}
	do{
		if(atual->prox == lst->inicio || a->cod < atual->prox->cod){
			Item* prox=atual->prox;
			
			a->prox=prox;
			a->ant=atual;
			atual->prox=a;
			atual->ant=a;
			lst->qtd++;
			return;
		}
		atual=atual->prox;
	}while(atual!=lst->inicio);
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
