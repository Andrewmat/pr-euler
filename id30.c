#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 13/09/2014
 * Function: Problem 30 - Project Euler
*/

#define NUM 5
#define DIGS 6

//5 digits tops
int i[DIGS];
int soma;

int funcao(int x, int y, int dig){
	for(i[dig] = 0; i[dig] < 10; i[dig]++){
		x += i[dig] * pow(10,DIGS-dig-1);
		y += pow(i[dig], NUM);
		if(dig == DIGS-1){
			if(x == y && x > 1){
				printf("%d\n", x);
				soma += x;
			}
		}
		else{
			funcao(x,y,dig+1);
		}
		x -= i[dig] * pow(10,DIGS-dig-1);
		y -= pow(i[dig], NUM);
	}
}

int main(int argc, const char* argv[]){
	int x=0,y=0;
	soma = 0;

	funcao(x,y,0);
	printf("\n\n----------------\nSOMA: %d\n----------------------\n", soma);

	system("pause");
	return 0;
}
