#include <iostream>

void pascal(int n){
	for(int i=1; i<=n; i++){
		int A=1;
		for(int j=1; j<=i; j++){
			std::cout<<A<<" ";
			A = A * (i-j)/j;
			}
			std::cout<<"\n";
		}
}

int main(){
	const int N = 7;
	pascal(N);
	return 0;
}

	
