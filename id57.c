#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 24/09/2014
 * Function: Problem 57 - Project Euler
*/

int countDig(unsigned long long x){
	int i=0;
	while(x > pow(10,++i));
	return i;
}

int main(int argc, const char* argv[]){
	int i;
	unsigned long long a=1,b=2,ax;
	int resp=0;
	for(i=0; i<1000;i++){
		ax=a+b;
		printf("%d: %lld/%lld\n",i,ax,b);
		getch();
		if(countDig(ax) > countDig(b)){
			resp++;
		}
		//Next
		ax = a;
		a = b;
		b = 2*b+ax;
	}

	printf("\n----------------\n%d\n----------------\n",resp);

	//system("pause");
	return 0;
}
