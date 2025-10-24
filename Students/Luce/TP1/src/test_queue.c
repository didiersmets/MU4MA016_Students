#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"




int main(int argc, char *argv[]){

    struct Queue *q = queue_init(sizeof(int),10);

    srand(time(NULL));
    int p;
    int l_max = 0;
    
    
    for(int i=0; i<atoi(argv[1]); i++){
        p = rand()%6*2+1;
        printf("tour %d p=%d\n",i+1,p);
        
        if ( p%2 == 1 ){

            //printf("p=%d entre dans la queue\n",p);
            queue_enqueue(q,&p);

            if (q->length>l_max){
                l_max=q->length;
            }

        } else {

            if (q->length==0){
                printf("p=%d ne fait rien\n",p);
            }

            void *dest=malloc(sizeof(q->elem_size));
            queue_dequeue(q, dest);
            int QuiEstCe = *(int *)dest;
            if (p==QuiEstCe){
                printf("%d est sorti de la queue\n", QuiEstCe);
            }
            free(dest);
            }
    }
    printf("l_max = %d\n", l_max);



    //affiche le contenu de la queue
    int taille = 0;
    int* adresse_valeur;

    while(taille < q->length){

        adresse_valeur = (int*)(char *)q->data + q->elem_size*( ( q->front + taille ) % q->capacity);
        printf("truc : %zu\n, q->data : %p, adresse_valeur %p\n",q->elem_size*( ( q->front + taille ) % q->capacity), (int*)(char *)q->data, (int*)(char *)q->data + q->elem_size*( ( q->front + taille ) % q->capacity) );
        //printf("q->data : %p\nadresse valeur : %p, valeur : %d\n",q->data,adresse_valeur,*adresse_valeur);
        
        taille++;
    }

    queue_dispose(q);

    return 0;   
}