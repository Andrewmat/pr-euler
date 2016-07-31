#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/*
 * Author: Andre M. Santos
 * Date: 23/09/2014
 * Function: Problem 78 - Project Euler
*/
#define MAX 200
#define DIV 1000000

unsigned long long funcao(int ant, int tam){
	int atual = tam < ant ? tam : ant;
	unsigned long long x = 0;
	if(atual == 1 || atual == 0){
		return 1;
	}
	else{
		do{
			x += funcao(atual,tam-atual);
			atual--;
		} while(atual >= 1);
	}
	return x;
}

int main(int argc, const char* argv[]){
	int i;
	unsigned long long aux, auxAnt=0;
	for(i = 5; i < MAX; i++){
		printf("%d",i);
		aux = funcao(i-1,i);
		printf(" -> %lld\n",aux);
		if(aux % DIV == 0){
			printf("\nPara n=%d,p(n) eh divisivel por %d\n",i,DIV);
			break;
		}
		else if(aux < auxAnt){
			printf("\nLIMITE ESTOURADO\n");
			break;
		}
		auxAnt = aux;
	}

	return 0;
}
