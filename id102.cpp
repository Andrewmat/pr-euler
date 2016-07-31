#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using namespace std;

class ponto{
public:
	double x,y,z;
	ponto(double a, double b, double c){
		x = a; y = b; z = c;
	}
	ponto(double a,double b){
		x = a; y = b; z = 0;
	}
	ponto(void){
		x = 0; y = 0; z = 0;
	}
	ponto operator+(ponto p){
		return ponto(x+p.x, y+p.y, z+p.z);
	}
	ponto operator-(ponto p){
		return ponto(x-p.x, y-p.y, z-p.z);
	}
	ponto produtoVetor(ponto p){
		double a = y*p.z - p.y*z;
		double b = x*p.z - p.x*z;
		double c = x*p.y - p.x*y;
		return ponto(a,b,c);
	}
	double produtoEscalar(ponto p){
		return (x*p.x + y*p.y + z*p.z);
	}
	bool mesmoLado(ponto p1, ponto p2){
		ponto cp1 = produtoVetor(p1);
		ponto cp2 = produtoVetor(p2);
		if (cp1.produtoEscalar(cp2) >= 0) return true;
		else return false;
	}
};

const int N_TRI = 1000;
ponto triang[N_TRI][3];

bool readFile(void);

bool pontoIn(ponto p, ponto a, ponto b, ponto c){
	ponto vet;
	vet = b-a;
	if(!vet.mesmoLado(p-a,c-a)) return false;
	vet = c-b;
	if(!vet.mesmoLado(p-b,a-b)) return false;
	vet = a-c;
	if(!vet.mesmoLado(p-c,b-c)) return false;
	return true;
}

int main(){
	if(!readFile()) return 0;

	ponto o;
	int cnt = 0;
	for(int i = 0; i < N_TRI; ++i){
		if(pontoIn(o, triang[i][0], triang[i][1], triang[i][2]))
			cnt++;
	}
	cout << cnt << endl;

	return 0;
}

bool readFile(){
	ifstream arq("resources/102_triangles.txt");
	if(!arq.is_open()){
		cout << "Problema na abertura do arquivo" << endl;
		return false;
	}
	else{
		int x, y;
		for(int i = 0; i < N_TRI; ++i){
			for(int j = 0; j < 3; ++j){
				arq >> x;
				arq >> y;
				triang[i][j] = ponto(x,y);
			}
		}
		arq.close();
		return true;
	}
}
