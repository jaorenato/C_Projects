#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

//PROJETO SISTEMA ACADEMICO
//FACA UM PROGRAMA QUE IMPLEMENTE DUAS STRUCTS:
	//DISCENTE: NOME:S, MATRICULA:I, NOTAS:A, COEF.RENDIMENTO:F
	//DISCIPLINAS: COD:I, NOME:S, CH:I, DISCENTES:A
//OPÇÕES NA INTERFACE:
	//1 - CADASTRAR DISCIPLINA
	//2 - CADASTRAR ALUNO
	//3 - MATRICULAR ALUNO
	//4 - LANÇAR NOTAS
	//5 - DIARIO DA DISCIPLINA
	//6 - HISTORICO DO ALUNO
	//7 - RANKING DE CR
//REQUISITOS:
	//MATRICULA(DISCENTE) E COD(DISCIPLINA) SÃO CAMPOS CHAVE.
	//MATRICULA EM CADA DISCIPLINA DEVE SER UNICA.
	//NOTA EM CADA DISCIPLINA DEVE SER UNICA.
	//DIARIO DA DISCIPLINA DEVE IMPRIMIR TODOS OS ALUNOS 
		//MATRICULADOS E SUAS RESPECTIVAS NOTAS
	//HISTORICO DO ALUNO DEVE IMPRIMIR TODOS SUAS DISCIPLINAS 
		// SUAS RESPECTIVAS NOTAS
	//RANKING DE CR, RELATORIO DE ALUNOS
		//ORDENADO DE FORMA DECRESCENTE POR CR

typedef struct{
	char nome[100];
	int codigo;
	int ch; //carga horaria
	char professor[100];
	int discentes[100];
	int cont_disc;  //qtde alunos matriculados
}Disciplina;

typedef struct{
	int matricula;
	char nome[100];
	int notas[100][2];
	int cont_notas;
	float cr;
}Discente;


Disciplina setDisciplina(int codigo){
	Disciplina nova;
	//técnica de reescrever função - input
	input("Informe o Nome da Disciplina",STR, nova.nome);
	nova.codigo = codigo;
	input("Informe a CH da Disciplina",INT, &nova.ch);
	input("Informe o Professor da Disciplina", STR, nova.professor);
	nova.cont_disc = 0;
	printf("Disciplina Cadastrada - Código: %d\n",nova.codigo);
	return nova;
}

Discente setDiscente(int mat){
	Discente novo;
	novo.matricula = mat;
	printf("Matrícula: %d\n",mat);
	input("Nome do Aluno",STR,novo.nome);
	novo.cr = 0;
	novo.cont_notas = 0;
	printf("Discente %s cadastrado com sucesso!\n",novo.nome);
	return novo;
}

int interface(){
	int opt;
	printf("1 - Cadastrar Disciplina\n");
	printf("2 - Cadastrar Discente\n");
	printf("3 - Matricular Discente\n");
	printf("4 - Lançar Notas\n");
	printf("5 - Diário da Disciplina\n");
	printf("6 - Histórico do Aluno\n");
	printf("7 - Maiores CRs\n");
	printf("0 - ENCERRAR PROGRAMA\n");
	scanf(" %d",&opt);
	return opt;
}

int buscarDisciplina(char* str, Disciplina* d, int c){
	for(int i=0; i < c; i++)
		if(!strcmp(str,d[i].nome))
			return i;
	return -1;
}

int buscarDiscente(char* str, Discente* d, int c){
	for(int i=0; i < c; i++)
		if(!strcmp(str,d[i].nome))
			return i;
	return -1;
}

int getNomeAluno(Discente* alunos, int cd, int matricula){
	for(int i=0; i < cd; i++)
		if(alunos[i].matricula == matricula){
			printf("%s\n",alunos[i].nome);
			return i;
		}
	return -1;
}

void getDiario(Disciplina* matriz, int cont, Discente* alunos, int ca){
	char alvo[100];
	input("Qual Disciplina deseja Buscar?",STR,alvo);
	int local = buscarDisciplina(alvo,matriz,cont);
	if(local<0){
		printf("Disciplina Inexistente\n");
		return;
	}
	printf("Nome da Disciplina: %s\n",matriz[local].nome);
	printf("CH da Disciplina: %d\n",matriz[local].ch);
	printf("Prof. da Disciplina: %s\n",matriz[local].professor);
	printf("Qtde. Alunos: %d\n",matriz[local].cont_disc);
	for(int i=0; i < matriz[local].cont_disc; i++)
		getNomeAluno(alunos,ca,matriz[local].discentes[i]);	
}

void rankingCR(Discente* alunos, int cont){
	printf("NOME\t\tMATRICULA\tCR\n");
	for(int i=0; i < cont; i++)
		printf("%s\t\t%d\t\t%.2f\n",
			alunos[i].nome,
			alunos[i].matricula,
			alunos[i].cr);
}


void matricularDiscente(Disciplina* matriz, int cd, Discente* alunos, int ca){
	char alvo[100];
	int aluno, disciplina;
	input("Qual Aluno deseja Matricular?",STR,alvo);
	aluno = buscarDiscente(alvo,alunos,ca);
	if(aluno<0){
		printf("Esse Aluno não Existe no Sistema\n");
		return;
	}
		
	input("Em qual Disciplina deseja Matricular? ",STR,alvo);
	disciplina = buscarDisciplina(alvo,matriz,cd);
	if(disciplina<0){
		printf("Essa Disciplina não Existe no Sistema\n");
		return;
	}
	
	int* alunos_disciplina = matriz[disciplina].discentes;
	int qtde_alunos = matriz[disciplina].cont_disc;
	
	alunos_disciplina[qtde_alunos] = alunos[aluno].matricula;
	matriz[disciplina].cont_disc++;
	printf("Aluno %s matriculado na disciplina %s\n",
		alunos[aluno].nome,
		matriz[disciplina].nome);
}

void lancarNotas(Disciplina* matriz, int cm, Discente* alunos, int ca){
	char alvo[100];
	input("Qual Disciplina Para Lançar Notas? ",STR, alvo);
	int disc = buscarDisciplina(alvo,matriz,cm);
	if(disc<0){
		printf("Disciplina Inexistente\n");
		return;
	}
	
	int* alunos_disciplina = matriz[disc].discentes;
	int pos_aluno;
	int nota;

	for(int i=0; i < matriz[disc].cont_disc; i++){
		printf("Nota para ");
		pos_aluno = getNomeAluno(alunos,ca,alunos_disciplina[i]);
		scanf(" %d",&nota);
	}

	Discente* d = &alunos[pos_aluno];

	int cn = d->cont_notas;
	d->notas[cn][0] = matriz[disc].codigo;
	d->notas[cn][1] = nota;
	d->cont_notas++;
}

void getHistorico(Discente* alunos, int ca){
	char alvo[100];
	input("Qual Aluno Deseja Historico? ",STR, alvo);
	int aluno = buscarDiscente(alvo,alunos,ca);
	if(aluno<0){
		printf("Aluno Inexistente\n");
		return;
	}	
	Discente* a = &alunos[aluno];
	
	printf("Nome: %s\n",a->nome);
	printf("Todas as Notas\n");
	for(int i=0; i < a->cont_notas; i++){
		printf("Disciplina: %d => %d\n",
			a->notas[i][0],
			a->notas[i][1]);
	}
}


int main(){
	//init data base
	Disciplina matriz[100];
	int cont_matriz = 0;
	Discente discentes[100];
	int cont_disc = 0;

	//controller da interface
	do{
		switch(interface()){
			case 1: matriz[cont_matriz] = setDisciplina(cont_matriz+1);
					cont_matriz++;
					break;
			case 2: discentes[cont_disc] = setDiscente(cont_disc+1);
					cont_disc++;
					break;
			case 3: matricularDiscente(matriz,cont_matriz,discentes,cont_disc);
					break;
			case 4: lancarNotas(matriz,cont_matriz,discentes,cont_disc);
					break;
			case 5: getDiario(matriz,cont_matriz, discentes, cont_disc);
					break;
			case 6: getHistorico(discentes,cont_disc);
					break;
			case 7: rankingCR(discentes,cont_disc);
					break;
			case 0: return 0;
		}
	}while(1);
	

}
