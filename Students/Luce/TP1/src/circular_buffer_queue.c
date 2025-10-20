#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/circular_buffer_queue.h"


//array based

bool is_empty(const struct Queue *q){
    return !q;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *new = malloc(elem_size * capacity);
    if (!new){
        printf("erreur");
        exit(1);
    }
    new->elem_size = elem_size;
    new->capacity = capacity;
    new->length = 0;
    new->front = 0;
    new->data = new ;
    return new;
}

void queue_dispose(struct Queue *q){
    if (!q){
        return;
    }

    free(q->data);
    free(q);
}

static void enlarge_queue_capacity ( struct Queue * q ){
        size_t new_cap = q->capacity == 0 ? 1 : 2*q->capacity;
        void *new_data = realloc(q->data, new_cap * q->elem_size);
        if (new_data != NULL){
            q->data = new_data;
            q->capacity = new_cap;
        } else {
            return;
        }    

}

void queue_enqueue(struct Queue *q, const void *src){
    if (!q){
        printf("Erreur, pas de file");
        return;
    }

    if (q->length >= q->capacity){
        enlarge_queue_capacity(q);
    }
    void *dest = (char *)q->data + q->elem_size * ((q->front + q->length) % q->capacity);
    printf("adresse src : %p, contenu de src : %d\n", src, *((int*) src));
    printf("queue_enequeue, q->front : %zu\n", q->front);
    memcpy(dest, src, q->elem_size);
    printf("apres memcpy\nadresse dest : %p, contenu de dest : %d\n", dest, *((int*) dest));
    q->length++;
    printf("queue_enequeue, q->front : %zu\n", q->front);
}

void queue_dequeue ( struct Queue *q , void * dest ){
    if(!q || q->length ==0){
        return;
    }
    void *src = (char*) q->data + q->elem_size*q->front;
    memcpy(dest, src, q->elem_size);
    q->length--;
    q->front = (q->front + 1) %q->capacity;
}

