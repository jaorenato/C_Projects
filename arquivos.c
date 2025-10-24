#include <stdio.h>
#include <stdlib.h>
#include "discentes.h"
#include "disciplinas.h"
#include "matriculas.h"

FILE* abrirArquivo(char* nome){
	FILE* arq = NULL;
	arq = fopen(nome,"rb+");
	if(!arq)
		arq = fopen(nome,"wb+");
	if(!arq)
		printf("Deu ruim hein!\n");
	return arq;
}

int interface(){
	printf("1 - Cadastrar Discente\n");
	printf("2 - Relatório Discentes\n");
	printf("3 - Cadastrar Disciplina\n");
	printf("4 - Matricular Discente\n");
	int opt;
	scanf(" %d",&opt);
	return opt;
}

void fecharArquivos(FILE* a,FILE* b,FILE* c){
	fclose(a);
	fclose(b);
	fclose(c);
}

int main(){
	FILE* discentes = abrirArquivo("discentes.dat");
	FILE* disciplinas = abrirArquivo("disciplinas.dat");
	do{
		switch(interface()){
			case 1: setDiscente(discentes);
					break;
			case 2: getDiscentes(discentes); 
					break;
			case 3: setDisciplina(disciplinas);
					break;
			case 0: //fecharArquivos();
					return 0;
					break;			
		}
	}while(1);
}
