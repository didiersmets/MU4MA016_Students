#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"




int main(){

    struct Queue *q = queue_init(sizeof(int),10);

    srand(time(NULL));
    int p = rand()%10;
    int i = 0;

    //vérifie que p ne change pas de valeur
    
 

    if ( p%2 == 1 ){
        queue_enqueue(q,&p);
        printf("adresse de p : %p, valeur de p : %d\n", &p,p);
    } else {
            if (q->length!=0){
            void *dest=NULL;
            queue_dequeue(q, dest);
            int *QuiEstCe = (int *)dest;
            printf("%d est sorti de la queue\n", *QuiEstCe);
        }
    }



    //affiche le contenu de la queue
    int taille = 0;
    int valeur;
    while(taille < (q->length)){
        //valeur = *(int *)((char *)q->data + q->elem_size*( ( q->front + taille ) % q->capacity));
        printf("adresse du premier élement de q : %p\n", q->data);
        
        void* dest = (char *)q->data + q->elem_size * ((q->front + taille) % q->capacity);
        printf("valeur :\n-q->length : %zu\n-q->front : %zu\n-taille:%d\n", q->length,q->front, taille);
        printf("adresse de valeur : %p\n",  dest);
        printf("valeur de valeur : %d\n", *((int*) dest));
        //printf("position %d : %d\n", taille+1, valeur);
        taille++;
    }

    return 0;   
}