#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    int *t;
    t = (int *) malloc(sizeof(int)*3);
    *t=1;
    *(t+1)=2;
    *(t+2)=3;

    printf("contenus du tableau :\n");
    for(int i=0; i<=2;i++){
        printf("%d\n",t[i]);
    }
    void* src = (char *) t;
    printf("///////////////////////\n");
    
    printf("test du cast d'un void* vers char* :\n");
    for(int i=0; i<=2;i++){
        printf("dans l'adresse %p : %d\n", ((int*) src)+i, *((int*) src)+i);
    }
    printf("///////////////////////\n");

    printf("test d'un memcpy :\n");
    void *dest = (char *) t;
    src = t+1; //étrange, il semble que t+1 est l'adresse de t+4
    printf("adresse de :\n-dest : %p\n-src : %p\n", dest, src);
    memcpy(dest,src,sizeof(int));
    printf("///////////////////////\n");

    printf("nouveau tableau, après memcpy :\n");
     for(int i=0; i<=2;i++){
        printf("%d\n",t[i]);
    }

    free(t);
}