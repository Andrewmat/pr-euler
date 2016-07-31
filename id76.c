#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 23/09/2014
 * Function: Problem 76 - Project Euler
*/
#define MAX 100

long long funcao(int ant, int tam){
	int atual = tam < ant ? tam : ant;
	long x = 0;
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
	printf("%lld\n",funcao(MAX-1,MAX));

//	system("pause");
	return 0;
}
