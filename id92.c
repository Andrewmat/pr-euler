#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 16/09/2014
 * Function: Problem 92 - Project Euler
*/

long i,j;

int main(int argc, const char* argv[]){
	long resp;
	for(i = 1; i < 10000000; i++){
		long num = i;
		long newnum = 0;
		int qDg = 0;
		while(num != 89 && num != 1){
			//printf("%d->",num);
			while(num >= pow(10,++qDg));
			do{
				newnum += pow((int)(num / pow(10,--qDg)),2);
				num = num % (long)pow(10,qDg);
			} while(num > 0);
			num = newnum;
			newnum = 0;
		}
		if(num == 89){
			resp++;
			//printf("\tX");
			//printf("%d\t%d\n", i,resp);
		}
		//printf("\n");
		//getch();
		if((i / 500000) * 500000 == i){
			printf("-->%d\n",i);
		}
	}

	printf("-=--=--=-\n%d\n", resp);

	//system("pause");
	return 0;
}
