#include <stdio.h>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
void Writing_program(int n){
    float x_min = -6*M_PI;
    float x_max = 6*M_PI;
    float x_delta = (x_max-x_min)/(n-1);
    std::ofstream fichier2("text_file.txt");
    for(int j=0;j<n;j++){
        float x = x_min+j*x_delta;
        float y = sin(x)/x;
        fichier2 << x <<"   " << y <<"\n";
    } 
    fichier2.close();
}




int main(){
    //Avec fopen
    /*std::FILE* f = std::fopen("test-tp0.txt", "r");
    
    if (f == NULL) {
        printf("File not found\n");
        return 0;
    }
    std::vector<char> buf(445);
    std::fread(&buf[0], sizeof buf[0], buf.size(), f);
    
    for (char n : buf)
        std::cout << n;
    std::cout << '\n';
    std::fclose(f);
    return 0;*/

    //Avec ifstream
    std::ifstream fichier("test-tp0.txt");
    if(!fichier.is_open()){
        printf("File not found\n");
        return 0;
    }
    char c;
    while(fichier.get(c)){
        std::cout << c;
    }
    fichier.close();
    Writing_program(4);
    return 0;
}