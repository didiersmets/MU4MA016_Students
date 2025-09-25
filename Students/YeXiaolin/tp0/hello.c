#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

int pascal(int i, int j){
    if(j>0&& j<i){
        return pascal(i-1,j-1) + pascal(i-1,j)
    else{
        return 1
    }

    }    
}