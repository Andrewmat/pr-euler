#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 23/09/2014
 * Function: Problem 82 - Project Euler
*/

#define TAM 80

int main(int argc, const char* argv[]){
	FILE *file = fopen("resources/82_matrix.txt","r");
	long m[TAM][TAM];
	long res[TAM][TAM];
	int lin,col;
	for(lin = 0; lin < TAM; lin++){
		for(col = 0; col < TAM; col++){
			fscanf(file,"%d,",&m[lin][col]);
		}
	}
	for(lin = 0; lin < TAM; lin++){
		//printf("%d\n",m[lin][0]);
		res[lin][0] = m[lin][0];
	}
	/*printf("\n");
	getch();*/
	for(col = 1; col < TAM; col++){
		for(lin = 0; lin < TAM; lin++){
			long sum, minSum=-1;
			int xlin;
			for(xlin = 0; xlin < TAM; xlin++){
				sum = 0;
				int aux;
				if(xlin < lin){
					for(aux = xlin; aux < lin; aux++){
						sum += m[aux][col];
					}
				}
				else if(xlin > lin){
					for(aux = xlin; aux > lin; aux--){
						sum += m[aux][col];
					}
				}
				sum += res[xlin][col-1];
				if(sum < minSum || minSum < 0){
					minSum = sum;
				}
			}
			res[lin][col] = m[lin][col]+minSum;
		}
		/*
		for(lin = 0; lin < TAM; lin++){
			printf("%d\n",res[lin][col]);
		}
		printf("\n");
		getch();*/
	}
	int minCam = -1;
	for(lin = 0; lin < TAM; lin++){
		if(res[lin][col-1] < minCam || minCam < 0){
			minCam = res[lin][col-1];
		}
	}
	printf("\n-=-=-=-=-\n%d\n-=-=-=-=-\n",minCam);

	//system("pause");
	return 0;
}
