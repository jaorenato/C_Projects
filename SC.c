#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5

int main(){
	float M[MAX][MAX];
	srand(time(NULL));
	for(int i=0; i<MAX; i++)
		for(int j=0; j<MAX; j++)
			M[i][j]=rand()%100;
	printf("MATRIZ INICIAL:\n");
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++)
			printf(" %.2f\t ",M[i][j]);
		printf("\n");
	}
	for(int i=0; i<MAX; i++){
		float x=M[i][i];
		if(x!=0)
			for(int j=0; j<MAX; j++)
				M[i][j]=M[i][j]/x;
	}
	printf("\nMATRIZ RESULTANTE:\n");
	for(int i=0; i<MAX; i++){
		for(int j=0; j<MAX; j++)
			printf(" %.2f\t ",M[i][j]);
		printf("\n");
	}
	return 0;
}
