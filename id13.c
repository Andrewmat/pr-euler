#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 14/09/2014
 * Function: Problem 13 - Project Euler
*/

 #define QTD_NMB 100
 #define QTD_DIG 50

void read();
char nmb[QTD_NMB][QTD_DIG];
int sum[QTD_DIG];
int i,j;

int main(int argc, const char* argv[]){
	read();
	for(i=0; i < QTD_DIG;i++){
		sum[i]=0;
	}
	for(j=QTD_DIG-1; j >= 0; j--){
		for(i = 0; i < QTD_NMB; i++){
			sum[j] += nmb[i][j] - '0';
		}
	}
	for(j=QTD_DIG-1; j >= 1; j--){
		if(sum[j] >= 10){
			sum[j-1] += sum[j] / 10;
			sum[j] = sum[j] % 10;
		}
	}
	i=0,j=0;
	while(sum[i++] == 0);
	for(j=i-1; j<=i+9; j++) printf("%d",sum[j]);
	printf("\n");

	system("pause");
	return 0;
}

void read(){
	FILE *arq;
	arq = fopen("resources/13_numbers.txt","r");

	for(i = 0; i < QTD_NMB; i++){
		for(j = 0; j < QTD_DIG; j++){
			fscanf(arq,"%c",&nmb[i][j]);
			if(nmb[i][j] == '\n'){
				fscanf(arq,"%c",&nmb[i][j]);
			}
		}
	}
}
