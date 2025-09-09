#include <iostream>
#include <fstream>

int main(){
    std::ifstream Fichier1("test-tp0.txt");
    std::string text("test");
    std::cout << "OK";
    while(Fichier1 >> text){
        std::cout << text;
    }
    return 0;
}