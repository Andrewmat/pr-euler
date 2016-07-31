#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 23/09/2014
 * Function: Problem 81 - Project Euler
*/

#define TAM 80

int main(int argc, const char* argv[]){
	FILE *file = fopen("resources/81_matrix.txt","r");
	long m[TAM][TAM];
	int i,j;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			fscanf(file,"%d,",&m[i][j]);
		}
	}
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(i == 0 && j == 0){
				m[i][j] = m[i][j];
			}
			else{
				if(i == 0){
					m[i][j] += m[i][j-1];
				}
				else if(j == 0){
					m[i][j] += m[i-1][j];
				}
				else{
					m[i][j] += m[i][j-1] < m[i-1][j] ? m[i][j-1] : m[i-1][j];
				}
			}
		}
	}
	printf("%d",m[TAM-1][TAM-1]);


	system("pause");
	return 0;
}
