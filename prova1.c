enum ARQ{USER=0, POST};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char nome[30], user[10], senha[10];
}User;

typedef struct{
	int id, valido;
	char conteudo[100];
}Post;

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

FILE *abrirFiles(char* nome){
	FILE* a=fopen(nome, "rb+");
	if(!a) a=fopen(nome, "wb+");
	if(!a){
		printf("Deu ruim!");
		wait();
		return NULL;
	}
	
	return a;
}

void fecharFiles(FILE** a, int c){
	for(int i=0; i<c; i++)
		fclose(a[i]);
	
	printf("Fechando aplicativo...");
	wait();
}

void novoUser(FILE** a){
	system("clear");
	User pessoa;
	
	fseek(a[USER], 0, SEEK_END);
	printf("=====================================================\n");
	printf("\t\tNOVO USUÁRIO\n");
	printf("=====================================================\n\n");

	printf("Digite seu Username:");
	scanf(" %[^\n]s", pessoa.user);
	printf("Digite seu nome:");
	scanf(" %s", pessoa.nome);
	printf("Digite sua senha:");
	scanf(" %s", pessoa.senha);
	
	if(fwrite(&pessoa, sizeof(User), 1, a[USER])){
		fflush(a[USER]);
		printf("Usuário cadastrado com sucesso!");
		wait();
	}
}

int interface(){
	system("clear");
	int opt;
	
	printf("\t\t\tREDE SOCIAL\n\n");
	printf("\t1) Novo Usuário\n");
	printf("\t2) Fazer Login\n");
	printf("\t3) Fechar Aplicação\n");
	scanf(" %d", &opt);

	return opt;
}

int telaPrincipal(FILE** a, char* n){
	system("clear");
	int op;
	User b;
	
	rewind(a[USER]);
	while(fread(&b, sizeof(User), 1, a[USER])){
		if(strcmp(b.nome, n)==0)
			printf("SEJA BEM VINDO <<<%s>>>\n\n", b.nome);
	}
		printf("4) Novo Post\n");
		printf("5) Listar Todos os Posts\n");
		printf("6) Excluir Post\n");
		printf("7) Alterar Senha\n");
		printf("8) Logout\n");
		scanf(" %d", &op);
		
		return op;
}

void novoPost(FILE** a){
	system("clear");
	Post p;
	
	fseek(a[POST], 0, SEEK_END);
	p.valido=1;
	p.id=rand()%1000;
    printf("Faça sua postagem:");
	scanf(" %[^\n]s", p.conteudo);
	
	if(fwrite(&p, sizeof(Post), 1, a[POST])){
		fflush(a[POST]);
		printf("Postagem feita!");
		wait();
	}
}

void listarPost(FILE** a, char* user){
	system("clear");
	Post p;

	fseek(a[POST], 0, SEEK_SET);
	while(fread(&p, sizeof(Post), 1, a[POST])){
		if(p.valido==1){
			printf("USERNAME: %s\n", user);
			printf("CONTEÚDO: %s", p.conteudo);
			printf("\nID: %d", p.id);
			printf("\n-------------------------------------------------------\n");
		}
	}
	wait();
}

void excluirPost(FILE** a){
	system("clear");
	int i;
	Post p;
	int v=0;
	
	printf("Informe o id do post que deseja excluir:");
	scanf(" %d", &i);
	
	printf("\n");
	rewind(a[POST]);
	while(fread(&p, sizeof(Post), 1, a[POST])){
		if(i==p.id){
			p.valido=0;
			v=1;
			wait();
			
			fseek(a[POST], -sizeof(Post), SEEK_CUR);
			if(fwrite(&p, sizeof(Post), 1, a[POST])){
				fflush(a[POST]);
				printf("Postagem excluida!");
			}
		}
		
	}
	
	if(!v){
		printf("ID inválido");
		wait();
		return;
	}
	wait();
}

void alterarSenha(FILE** a, char* user){
	system("clear");
	User b;
	
	rewind(a[USER]);
	while(fread(&b, sizeof(User), 1, a[USER])){
		if(strcmp(user, b.user)==0){
			printf("Digite a sua nova senha:");
			scanf(" %s", b.senha);
			
			fseek(a[USER], -sizeof(User), SEEK_CUR);
			if(fwrite(&b, sizeof(User), 1, a[USER])){
				fflush(a[USER]);
				printf("Senha alterada com sucesso!");
			}
		}
	}
	wait();
}

void menuPrincipal(FILE** a, char* user, char* nome){
	do{
		switch(telaPrincipal(a, nome)){
			case 4: novoPost(a);
					break;
			case 5: listarPost(a, user);
					break;
			case 6: excluirPost(a);
					break;
			case 7: alterarSenha(a, user);
					break;
			case 8: return;
			default: printf("Tente Novamente!");
		}
	}while(1);
}

void fazerLogin(FILE** a){
	system("clear");
	char nome[20], senha[20];
	User b;
	int c;
	
	do{
		system("clear");
		printf("Digite seu Username:");
		scanf(" %s", nome);
		printf("Digite sua senha:");
		scanf(" %s", senha);
		
		rewind(a[USER]);
		while(fread(&b, sizeof(User), 1, a[USER])){
			if((strcmp(nome, b.user)==0) && (strcmp(senha, b.senha)==0)){
				printf("Login concluido!");
				wait();
				menuPrincipal(a, b.nome, b.user);
				return;
			}else{
				printf("Login incorreto!Pressione '0' caso queira sair: ");
				scanf("%d", &c);
				if(!c) return;
				continue;
			}
		}
	}while(1);
}

int main(){
	srand(time(NULL));
	
	FILE* arq[2];
	arq[USER]=abrirFiles("user.dat");
	arq[POST]=abrirFiles("post.dat");
	
	do{
		switch(interface()){
			case 1: novoUser(arq);
					break;
			case 2: fazerLogin(arq);
					break;
			case 3: fecharFiles(arq, 2);
					 return 0;
			default: printf("Tente Novamente!");
		}
	}while(1);
}
