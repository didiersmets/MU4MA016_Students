#include <iostream>

void pascal(int n){
	for(int line = 1; line <= n; line++){
		int C = 1;
		for(int i = 1; i <= line; i++){
			std::cout<<C<<" ";
			C = C*(line - i)/i;
		}
		std::cout<<"\n";
	}
}

int main(){
	int n = 9;
	pascal(n);
	return 0;
}

