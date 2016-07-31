#include <cmath>
#include <iostream>
#include <cstdio>
using namespace std;
/* Problem 56 - Project Euler */
int main(){
	int a,b;
	int max = 0;
	int errcnt = 0;
	for(a = 1; a <= 100; ++a){
		for(b = 1; b <= 100; ++b){
			double aux = (double)b*(double)log10(a);
			int auxfloor = (int)floor(aux);
			int alpha[auxfloor];
			alpha[auxfloor - 1] = (int)pow(10, aux - auxfloor);
			for(int i = auxfloor - 2; i >= 0; --i){
				alpha[i] = (int)(pow(10,aux-i) - alpha[i+1]*pow(10,i+2));
				if(alpha[i] >= 10){
					cout<<"Erro:("<<a<<"^"<<b<<")"<<endl;
					cout<<"alpha["<<i<<"]: 10^"<<aux-i<<" - "<<alpha[i+1]<<"*10^"<<i+2<<endl;
					cout<<"b log a:"<<aux<<endl;
					//std::cout << "Erro!" << a << "^" << b << "\talpha[" << i <<"]: " << alpha[i] << std::endl;
					errcnt++;
					getchar();
				}
			}
			int count = 0;
			for(int i = 0; i < auxfloor; ++i){
				count += alpha[i];
			}
			if(count > max){
				max = count;
			}
		}
	}
	std::cout << max << "\te:" << errcnt << std::endl;
}
