#include <iostream>
/*
Construire cmake liste
1) Faire CMakeLists.txt dans dir
2) Ecrire:
    cmake_minimum_required(VERSION 3.14)
    project(tp0)

    add_executable(hello
	    hello.cpp
    )
3) Faire dans terminal:
    cmake -B build/
    cmake --build build
4) Executer avec:
    ./build/hello

*/
int Pascal_formula(int i,int j){ 
    if( j>0 && j<i ){
        return Pascal_formula(i-1,j-1)+Pascal_formula(i-1,j);
    }
    else{
        return 1;
    }
}

int main(){
    std::cout << "Hello World\n";
    std::cout << "Triangle de Pascal\n";
    int n=5;
    for(int i=0 ; i<=n ; i++){
        for(int j=0 ; j<=i ; j++){
            std::cout << Pascal_formula(i,j) <<" ";
        }
        std::cout << "\n";
    }
    return 0;
}

