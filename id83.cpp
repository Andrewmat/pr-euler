#include <iostream>
#include <fstream>
using namespace std;

const int SIZE_H = 80;
const int SIZE_V = 80;
int mat[SIZE_V][SIZE_H];
int dst[SIZE_V][SIZE_H];
char dir[SIZE_V][SIZE_H];

bool readFile(void);

int main(){
	if(!readFile()) return false;
	bool mudanca;
	dst[0][0] = mat[0][0];
	dir[0][0] = 'x';
	int it = 0;
	do{
		mudanca = false;
		for(int i = 0; i < SIZE_V; ++i){
			for(int j = 0; j < SIZE_H; ++j){
				if(i != 0){
					if(dir[i-1][j] != 'n' && (dir[i][j] == 'n' || dst[i][j] > dst[i-1][j] + mat[i][j])){	// CIMA
						dst[i][j] = dst[i-1][j] + mat[i][j];
						dir[i][j] = 'c';
						mudanca = true;
					}
				}
				if(j != 0){
					if(dir[i][j-1] != 'n' && (dir[i][j] == 'n' || dst[i][j] > dst[i][j-1] + mat[i][j])){	// ESQUERDA
						dst[i][j] = dst[i][j-1] + mat[i][j];
						dir[i][j] = 'e';
						mudanca = true;
					}
				}
				if(i != SIZE_V-1){
					if(dir[i+1][j] != 'n' && (dir[i][j] == 'n' || dst[i][j] > dst[i+1][j] + mat[i][j])){	// BAIXO
						dst[i][j] = dst[i+1][j] + mat[i][j];
						dir[i][j] = 'b';
						mudanca = true;
					}
				}
				if(j != SIZE_H-1){
					if(dir[i][j+1] != 'n' && (dir[i][j] == 'n' || dst[i][j] > dst[i][j+1] + mat[i][j])){	// DIREITA
						dst[i][j] = dst[i][j+1] + mat[i][j];
						dir[i][j] = 'd';
						mudanca = true;
					}
				}
			}
		}
	} while(mudanca);
	cout << dst[SIZE_V-1][SIZE_H-1] << endl;

	return 0;
}

bool readFile(){
	ifstream arq("resources/83_matrix.txt");
	if(!arq.is_open()){
		cout << "Problema na abertura do arquivo" << endl;
		return false;
	}
	else{
		for(int i = 0; i < SIZE_V; ++i){
			for(int j = 0; j < SIZE_H; ++j){
				arq >> mat[i][j];
				dst[i][j] = 0;
				dir[i][j] = 'n';
			}
		}
		arq.close();
		return true;
	}
}
