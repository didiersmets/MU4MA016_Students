#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    char s[3];
    int i = 0;
    while (i<3){
        s[i] = (char) 97+i;
        i++;
    }
 
        
        printf("%s \n",s);
    
}