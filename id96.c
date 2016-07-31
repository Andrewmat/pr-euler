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

#define OK -1
#define ERROR_EOF -2

int sud[TAM][TAM][TAM];
int sudguess[TAM][TAM][TAM];
int nSud;
int erSud;
FILE* file;

int clearAll();
int read();
int def(int, int, int);
int defAll();
int undef(int, int, int);
int undefRowCol(int, int, int);
int undefGroup(int, int, int);

/* Auxiliars */

int valueOf(int, int);
int countPsb(int, int);
int isComplete();

/* Shows */

void showSud();
void showCountPsb();
void showAllPsb();

/* Guess */

void copytoGuess();
int defGuess(int, int, int);
int defAllGuess();
int undefGuess(int, int, int);
int undefRowColGuess(int, int, int);
int undefGroupGuess(int, int, int);
int valueOfGuess(int, int);
int countPsbGuess(int, int);
int tryGuess(int, int, int);
int tryAllGuesses(int);

/* END: Constants, variables and prototypes */

/* Main */
int main(int argc, const char* argv[]){
	file = fopen("resources/96_sudokus.txt","r");
	do{
		read();
		defAll();
		int tol;
		if(!isComplete()){
			for(tol = 2; tol <= TAM; tol++){
				while(tryAllGuesses(tol) > 0)
					tol = 2;
			}
		}
		if(!isComplete()){
			printf("%d:\n",nSud);
			printf("\n");
		}
	} while(nSud < 50);
	fclose(file);

	return 0;
}

int clearAll(){
	int i,j,k;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			for(k = 0; k < TAM; k++){
				sud[i][j][k] = 1;
				sudguess[i][j][k] = 0;
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

	clearAll();
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
				def(i,j,num-1);
			}
		}
	}

	return resp;
}

/*
	Function: define cell (x,y) as the number num
	Returns: number of changes made
*/
int def(int x, int y, int num){
	int k, resp = 0;
	resp += undefRowCol(x,y,num);
	resp += undefGroup(x,y,num);
	for(k = 0; k < TAM; k++){
		if(k == num && sud[x][y][k] != 1){
			sud[x][y][k] = 1;
			resp--;
		}
		else if(k != num && sud[x][y][k] != 0){
			sud[x][y][k] = 0;
			resp++;
		}
	}

	return resp;
}

/*
	Function: if cell only have a possibility, define cell, for every cell
	Returns: number of changes made
*/
int defAll(){
	int i,j,k, resp = 0, respAnt = 0;
	do{
		respAnt = resp;
		for (i = 0; i < TAM; i++){
			for (j = 0; j < TAM; j++){
				if(countPsb(i,j) == 1){
					resp += def(i,j,valueOf(i,j));
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
int undef(int x, int y, int num){
	if(sud[x][y][num] == 1){
		sud[x][y][num] = 0;
		return true;
	}
	else
		return false;
}

/*
	Function: Take off the possibility num from the row x and the column y
	Returns: number of changes made
*/
int undefRowCol(int x, int y, int num){
	int resp = 0;
	int i;
	for(i = 0; i < TAM; i++){
		resp += undef(x,i,num);
		resp += undef(i,y,num);
	}
	return resp;
}

/*
	Function: Take off the possibility num from the group of (x,y)
	Returns: number of changes made
*/
int undefGroup(int x, int y, int num){
	int resp = 0;
	int i,j;
	for(i = x - (x % 3); i < x + 3 - (x % 3); i++){
		for(j = y - (y % 3); j < y + 3 - (y % 3); j++){
			resp += undef(i,j,num);
		}
	}
	return resp;
}

/* Auxiliars */

/*
	Function: Find the value of cell (x,y)
	Returns: The only possibility of the cell. If there is not just 1 possibility, returns -1
*/
int valueOf(int x, int y){
	int k;
	if(countPsb(x,y) != 1)  return -1;
	for(k = 0; k < 9; k++){
		if(sud[x][y][k] == 1) return k;
	}
}

/*
	Function: Count the possibilities of cell (x,y)
	Returns: Total of possibilities in this cell
*/
int countPsb(int x, int y){
	int k, resp = 0;
	for(k = 0; k < TAM; k++){
		resp += sud[x][y][k];
	}
	return resp;
}

int isComplete(){
	int i,j;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(countPsb(i,j) != 1)
				return false;
		}
	}
	return true;
}

/* Function: Show the sudoku array on screen */
void showSud(){
	int i,j,x;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(j != 0 && j % 3 == 0)
				printf(" |");
			printf(" %d", valueOf(i,j)+1);
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
void showCountPsb(){
	int i,j,x;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(j != 0 && j % 3 == 0)
				printf(" |");
			printf(" %d", countPsb(i,j));
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
void copytoGuess(){
	int i,j,k;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			for(k = 0; k < TAM; k++){
				sudguess[i][j][k] = sud[i][j][k];
			}
		}	
	}
}

/*
	For guess table
	Function: define cell (x,y) as the number num
	Returns: number of changes made
*/
int defGuess(int x, int y, int num){
	int k, resp = 0;
	resp += undefRowColGuess(x,y,num);
	resp += undefGroupGuess(x,y,num);
	for(k = 0; k < TAM; k++){
		if(k == num && sudguess[x][y][k] != 1){
			sudguess[x][y][k] = 1;
			resp--;
		}
		else if(k != num && sudguess[x][y][k] != 0){
			sudguess[x][y][k] = 0;
			resp++;
		}
	}

	return resp;
}

/*
	For guess table:
	Function: if cell only have a possibility, define cell, for every cell
	Returns: number of changes made
*/
int defAllGuess(){
	int i,j,k, resp = 0, respAnt = 0;
	do{
		respAnt = resp;
		for (i = 0; i < TAM; i++){
			for (j = 0; j < TAM; j++){
				if(countPsbGuess(i,j) == 1){
					resp += defGuess(i,j,valueOfGuess(i,j));
				}
			}
		}
	} while(resp > respAnt);

	return resp;
}

/*
	For guess table
	Function: Take off the possibility num from (x,y)
	Returns: if it was changed
*/
int undefGuess(int x, int y, int num){
	if(sudguess[x][y][num] == 1){
		sudguess[x][y][num] = 0;
		return true;
	}
	else
		return false;
}

/*
	For guess table
	Function: Take off the possibility num from the row x and the column y
	Returns: number of changes made
*/
int undefRowColGuess(int x, int y, int num){
	int resp = 0;
	int i;
	for(i = 0; i < TAM; i++){
		resp += undefGuess(x,i,num);
		resp += undefGuess(i,y,num);
	}
	return resp;
}

/*
	For guess table
	Function: Take off the possibility num from the group of (x,y)
	Returns: number of changes made
*/
int undefGroupGuess(int x, int y, int num){
	int resp = 0;
	int i,j;
	for(i = x - (x % 3); i < x + 3 - (x % 3); i++){
		for(j = y - (y % 3); j < y + 3 - (y % 3); j++){
			resp += undefGuess(i,j,num);
		}
	}
	return resp;
}

/*
	For guess table
	Function: Find the value of cell (x,y)
	Returns: The only possibility of the cell. If there is not just 1 possibility, returns -1
*/
int valueOfGuess(int x, int y){
	int k;
	if(countPsbGuess(x,y) != 1)  return -1;
	for(k = 0; k < 9; k++){
		if(sudguess[x][y][k] == 1) return k;
	}
}

/*
	Function: Count the possibilities of cell (x,y)
	Returns: Total of possibilities in this cell
*/
int countPsbGuess(int x, int y){
	int k, resp = 0;
	for(k = 0; k < TAM; k++){
		resp += sudguess[x][y][k];
	}
	return resp;
}

/*
	Function: Try guess in cell (x,y).
	Returns: If there is any absurd, undef(x,y,guess) and returns number of changes made. Else returns false.
*/
int tryGuess(int x, int y, int guess){
	int i,j,k;

	defGuess(x,y,guess);
	defAllGuess();

	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			if(countPsbGuess(i,j) == 0){
				undef(x,y,guess);
				return defAll()+1;
			}
		}
	}
	return false;
}

/*
	Function: Try guesses for all the table
	Returns: number of changes made
	param=tol: guesses in a cell. Ie: if tol=2, cells with 2 possibilities can be guessed.
*/
int tryAllGuesses(int tol){
	int i,j,k, resp = 0;
	copytoGuess();

	//For every cell
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			//If there is "tol" possibilities
			if(countPsbGuess(i,j) == tol){
				for(k = 0; k < TAM; k++){
					//Try every possibility
					if(sud[i][j][k] == 1){
						int aux = tryGuess(i,j,k);
						if(aux != false){
							resp += aux;
						}
						copytoGuess();
					}
				}
			}
		}
	}

	return resp;
}

void showAllPsb(){
	int i,j,l;
	for(i=0; i < TAM; i++){
		for(l = 0; l < 3; l++){
			for(j = 0; j < TAM; j++){
				printf(" %d %d %d |",sud[i][j][3*l],sud[i][j][3*l+1],sud[i][j][3*l+2]);
			}
			printf("\n");
		}
		printf("------------------------------------------------------------------------\n");
	}
}
