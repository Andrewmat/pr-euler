#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 15/09/2014
 * Function: Problem 34 - Project Euler
*/

int i,j;

long fat(int n){
	switch(n){
		case 0:
		case 1:
		return 1;
		case 2:
		return 2;
		case 3:
		return 6;
		case 4:
		return 24;
		case 5:
		return 120;
		case 6:
		return 720;
		case 7:
		return 5040;
		case 8:
		return 40320;
		case 9:
		return 362880;
		default:
		printf("ERRO");
		getch();
		return -1;
	}
}

int main(int argc, const char* argv[]){
	int resp = 0;
	char ch[8];
	long num,sum;
	int qtdDig;
	for(num=3; num < 99999999; num++){
		sum = 0;
		itoa(num,ch,10);
		qtdDig=0;
		while(num > pow(10,++qtdDig));
		for(i=0; i < qtdDig; i++){
			sum += fat(ch[i]-'0');
		}
		if(sum == num){
			printf("%d\t<-\n", sum);
			resp += sum;
		}
		if(((long)num / 5000000) * 5000000 == num){
			printf("%d\n", num);
		}
	}

	printf("-=--=--=-\n%d\n", resp);

	//system("pause");
	return 0;
}
