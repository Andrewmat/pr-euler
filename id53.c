#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 16/09/2014
 * Function: Problem 53 - Project Euler
*/

int i,j;

int main(int argc, const char* argv[]){
	int n,k,resp=0;
	for(n = 23; n <= 100; n++){
		long val = 1;
		for(k = 1; k <= n/2 ; k++){
			val = round((double)val * (double)(n-(k-1))/(double)k);
			if(val > 1000000)
				break;
		}
		if((n/2)*2 == n){		//Even
			resp += (2*((n/2)-k))+1;
		}
		else{					//Odd
			resp += (2*((n/2)-k+1));
		}
	}

	printf("%d\n",resp);

	//system("pause");
	return 0;
}
