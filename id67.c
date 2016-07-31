#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 14/09/2014
 * Function: Problem 67 - Project Euler
*/

#define SIZE 100

int m[SIZE][SIZE], m2[SIZE][SIZE];
int i, j;
void read();

int main(int argc, const char* argv[]){
	read();

	for(i=1; i < SIZE; i++){
		for(j = 0; j <= i; j++){
			//Pegar valores na linha anterior pra aumentar pra linha atual
			if(j == 0){
				m[i][j] += m[i-1][j];	//Inicio da linha, pega valor anterior unico
			}
			else if(j == i){
				m[i][j] += m[i-1][j-1];	//Fim da linha, pega valor anterior unico
			}
			else{
				m[i][j] += m[i-1][j] > m[i-1][j-1] ? m[i-1][j] : m[i-1][j-1];	//Meio da linha, escolhe qual valor eh o menor
			}
			//printf(" %d",m[i][j]);
		}
		//printf("\n");
		//getch();
	}
	
	int max=0;
	for(j=0; j < SIZE; j++){
		if(max == 0 || max < m[SIZE-1][j]){
			max = m[SIZE-1][j];
		}
	}
	
	printf("%d\n",max);

	//system("pause");
	return 0;
}

void read(){
	FILE* ftxt;
	ftxt = fopen("resources/67_triangles.txt","r");
	for(i = 0; i < SIZE; i++){
		for(j = 0; j <= i; j++){
			fscanf(ftxt,"%d",&m[i][j]);
		}
	}
	fclose(ftxt);
}
