#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



int main(){


    void* p = malloc(sizeof(int)*2);
    int q=3;
    int k=4;
    memcpy(p,&q,sizeof(int));
    void *dest = (char *)p + sizeof(int);
    memcpy(dest,&k,sizeof(int));

    //printf("%d\n",*(int*) p);     OK
    //printf("%d\n", *(int*)(p+4));  OK



    size_t a = 1;
    int b = 1;  //a+b = 5 OK

    int *adresse_valeur;

    for(int i=0; i<2;i++){
        adresse_valeur = (int*)(char *)p + i*a;
        printf("%d\nadresse_valeur = %p\nadresse de p : %p\n", *adresse_valeur, adresse_valeur, p);

        
    }

}