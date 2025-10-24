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
    struct Queue *new = malloc(sizeof(struct Queue));
    void* new_data = malloc(elem_size * capacity);
    if (!new){
        printf("erreur\n");
        exit(1);
    }
    new->elem_size = elem_size;
    new->capacity = capacity;
    new->length = 0;
    new->front = 0;
    new->data = new_data;
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
    if (!q){
        printf("Erreur, pas de file\n");
        return;
    }
    size_t new_cap = q->capacity == 0 ? 1 : 2*q->capacity;
    //printf("nouvelle capacity %zu\n", new_cap);
    void *new_data = realloc(q->data, new_cap * q->elem_size);
    //printf("Après realloc: new_data=%p\n", new_data);
    if (new_data != NULL){
        q->data = new_data;
        q->capacity = new_cap;
    } else {
        printf("new_data  NULL!\n");
        return;
    }    

}

void queue_enqueue(struct Queue *q, const void *src){
    if (!q){
        printf("Erreur, pas de file\n");
        return;
    }
    void *dest = (char *)q->data + q->elem_size * ((q->front + q->length) % q->capacity);
    q->length++;
    printf("src : %d receptioned\n", *(int *)src);   
    //printf("length : %zu capacity : %zu\n", q->length, q->capacity);

    if (q->length >= q->capacity){
        size_t previous_capacity = q->capacity;
        enlarge_queue_capacity(q);
        printf("enlargement succeeded, nb of elements is %zu thus capacity goes from %zu to %zu\n",q->length, previous_capacity, q->capacity);
    }
    memcpy(dest, src, q->elem_size);
    printf("dest : %p, valeur dans dest : %d\n", dest, *(int*) dest);
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

