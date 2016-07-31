#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * Author: Andre M. Santos
 * Date: 18/09/2014
 * Function: Problem 96 - Project Euler - V2
*/

/* Constants, variables and prototypes */
#define TAM 9
#define N_SUD 50

#define OK -1
#define ERROR_EOF -2

int sud[TAM][TAM][TAM];
int nSud;
int erSud;
FILE* file;

int clearMain();
int read();
int def(int[TAM][TAM][TAM], int, int, int);
int defAll(int[TAM][TAM][TAM]);
int undef(int[TAM][TAM][TAM], int, int, int);
int undefRowCol(int[TAM][TAM][TAM], int, int, int);
int undefGroup(int[TAM][TAM][TAM], int, int, int);

/* Auxiliars */

int valueOf(int[TAM][TAM][TAM], int, int);
int countPsb(int[TAM][TAM][TAM], int, int);
int isComplete(int[TAM][TAM][TAM]);

/* Shows */

void showSud(int[TAM][TAM][TAM]);
void showCountPsb(int[TAM][TAM][TAM]);

/* Guess */

void copyto(int[TAM][TAM][TAM], int[TAM][TAM][TAM]);

int tryGuess(int[TAM][TAM][TAM], int[TAM][TAM][TAM], int, int, int, int, int);
int tryAllGuesses(int[TAM][TAM][TAM], int, int);

/* END: Constants, variables and prototypes */

/* RESPOSTA de Problem 96 */

int rsp = 0;
int resposta(){
	rsp += (valueOf(sud,0,0)+1)*100;
	rsp += (valueOf(sud,0,1)+1)*10;
	rsp += valueOf(sud,0,2)+1;
}

/* Main */
int main(int argc, const char* argv[]){
	file = fopen("resources/96_sudokus.txt","r");
	do{
		read();
		printf("%d:\n", nSud);
		defAll(sud);
		if(!isComplete(sud)){
			int level = 0;
			do{
				level++;
				int tol;
				for(tol = 2; tol < TAM; tol++){
					while(tryAllGuesses(sud,tol,level) > 0)
						tol = 2;
				}
			} while((!isComplete(sud)) && level < 3);
		}
		if(!isComplete(sud)){
			printf("ER: %d\n", nSud);
		}
		else{
			showSud(sud);
			printf("\n");
			resposta();
		}
	} while(nSud < N_SUD);
	fclose(file);
	
	printf("\n-=-=-=-=-\n%d\n-=-=-=-=-\n",rsp);

	return 0;
}

int clearMain(){
	int i,j,k;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			for(k = 0; k < TAM; k++){
				sud[i][j][k] = 1;
			}
		}
	}
}

/*
	Function: Read Su Doku array in var file and put it on sud[][][] by def(int,int,int)
	Returns: Number of read valid informations
*/
int read(){
	int i,j, num, resp=0;
	char cnum;

	clearMain();
	fscanf(file, "%d\n", &nSud);
	for(i = 0; i < TAM; i++){
		for (j = 0; j < TAM; j++){
			/* Read number */
			do{
				fscanf(file, "%c", &cnum);
				if(cnum == EOF){
					cnum = '0';
					break;
				}
			} while(cnum < '0' || cnum > '9');
			num = cnum - '0';
			resp++;

			/* define (X,Y) as num */
			if(num != 0){
				def(sud,i,j,num-1);
			}
		}
	}

	return resp;
}

/*
	Function: define cell (x,y) as the number num
	Returns: number of changes made
*/
int def(int table[TAM][TAM][TAM], int x, int y, int num){
	int k, resp = 0;
	resp += undefRowCol(table,x,y,num);
	resp += undefGroup(table,x,y,num);
	for(k = 0; k < TAM; k++){
		if(k == num && table[x][y][k] != 1){
			table[x][y][k] = 1;
			resp--;
		}
		else if(k != num && table[x][y][k] != 0){
			table[x][y][k] = 0;
			resp++;
		}
	}

	return resp;
}

/*
	Function: if cell only have a possibility, define cell, for every cell
	Returns: number of changes made
*/
int defAll(int table[TAM][TAM][TAM]){
	int i,j,k, resp = 0, respAnt = 0;
	do{
		respAnt = resp;
		for (i = 0; i < TAM; i++){
			for (j = 0; j < TAM; j++){
				if(countPsb(table,i,j) == 1){
					resp += def(table,i,j,valueOf(table,i,j));
				}
			}
		}
	} while(resp > respAnt);

	return resp;
}

/*
	Function: Take off the possibility num from (x,y)
	Returns: if it was changed
*/
int undef(int table[TAM][TAM][TAM], int x, int y, int num){
	if(table[x][y][num] == 1){
		table[x][y][num] = 0;
		return true;
	}
	else
		return false;
}

/*
	Function: Take off the possibility num from the row x and the column y
	Returns: number of changes made
*/
int undefRowCol(int table[TAM][TAM][TAM], int x, int y, int num){
	int resp = 0;
	int i;
	for(i = 0; i < TAM; i++){
		resp += undef(table,x,i,num);
		resp += undef(table,i,y,num);
	}
	return resp;
}

/*
	Function: Take off the possibility num from the group of (x,y)
	Returns: number of changes made
*/
int undefGroup(int table[TAM][TAM][TAM], int x, int y, int num){
	int resp = 0;
	int i,j;
	for(i = x - (x % 3); i < x + 3 - (x % 3); i++){
		for(j = y - (y % 3); j < y + 3 - (y % 3); j++){
			resp += undef(table,i,j,num);
		}
	}
	return resp;
}

/* Auxiliars */

/*
	Function: Find the value of cell (x,y)
	Returns: The only possibility of the cell. If there is not just 1 possibility, returns -1
*/
int valueOf(int table[TAM][TAM][TAM], int x, int y){
	int k;
	if(countPsb(table,x,y) != 1)  return -1;
	for(k = 0; k < 9; k++){
		if(table[x][y][k] == 1) return k;
	}
}

/*
	Function: Count the possibilities of cell (x,y)
	Returns: Total of possibilities in this cell
*/
int countPsb(int table[TAM][TAM][TAM], int x, int y){
	int k, resp = 0;
	for(k = 0; k < TAM; k++){
		resp += table[x][y][k];
	}
	return resp;
}

int isComplete(int table[TAM][TAM][TAM]){
	int i,j;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(countPsb(table,i,j) != 1)
				return false;
		}
	}
	return true;
}

/* Function: Show the sudoku array on screen */
void showSud(int table[TAM][TAM][TAM]){
	int i,j,x;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(j != 0 && j % 3 == 0)
				printf(" |");
			printf(" %d", valueOf(table,i,j)+1);
		}
		if(i != TAM-1 && i % 3 == 2){
			printf("\n");
			for(x = 0; x < TAM*2+4; x++)
				printf("-");
		}
		printf("\n");
	}
}

/* Function: Show the sudoku possibilities on screen, according to each cell */
void showCountPsb(int table[TAM][TAM][TAM]){
	int i,j,x;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(j != 0 && j % 3 == 0)
				printf(" |");
			printf(" %d", countPsb(table,i,j));
		}
		if(i != TAM-1 && i % 3 == 2){
			printf("\n");
			for(x = 0; x < TAM*2+4; x++)
				printf("-");
		}
		printf("\n");
	}
}

/* Guess */

/* Function: Copy main array to guess array */
void copyto(int source[TAM][TAM][TAM], int destiny[TAM][TAM][TAM]){
	int i,j,k;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			for(k = 0; k < TAM; k++){
				destiny[i][j][k] = source[i][j][k];
			}
		}	
	}
}

/*
	Function: Try guess in cell (x,y).
	Returns: If there is any absurd, undef(x,y,guess) and returns number of changes made. Else returns false.
*/
int tryGuess(int source[TAM][TAM][TAM], int guessTable[TAM][TAM][TAM],int x, int y, int guess, int tol, int level){
	int i,j,k;

	def(guessTable,x,y,guess);
	defAll(guessTable);

	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(countPsb(guessTable,i,j) == 0){
				undef(source,x,y,guess);
				return defAll(source)+1;
			}
		}
	}
	if(level > 1){
		int x = tryAllGuesses(guessTable, tol, level-1);
		if(isComplete(guessTable)){
			copyto(guessTable,sud);
			return x;
		}
	}
	return false;
}

/*
	Function: Try guesses for all the table
	Returns: number of changes made
	param=tol: guesses in a cell. Ie: if tol=2, cells with 2 possibilities can be guessed.
*/
int tryAllGuesses(int source[TAM][TAM][TAM], int tol, int level){
	int i,j,k, resp = 0;
	int guessTable[TAM][TAM][TAM];

	copyto(source,guessTable);

	//For every cell
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			//If there is "tol" possibilities
			if(countPsb(guessTable,i,j) == tol){
				for(k = 0; k < TAM; k++){
					//Try every possibility
					if(sud[i][j][k] == 1){
						int aux = tryGuess(source,guessTable,i,j,k,tol,level);
						if(aux != false){
							resp += aux;
						}
						copyto(source,guessTable);
					}
				}
			}
		}
	}
	
	return resp;
}

