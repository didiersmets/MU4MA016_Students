#include<stdbool.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct Queue{
	size_t front;
	size_t length;
	size_t capacity;
	size_t elem_size;
	void *data;
};

bool is_empty(const struct Queue *q){
	return q->length == 0;
}

size_t queue_length(const struct Queue *q){
	return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
	struct Queue *q = malloc(sizeof(struct Queue));
	if (!q) return NULL;
	q -> front = 0;
	q -> length = 0;
	q -> capacity = capacity;
	q -> elem_size = elem_size;
	q -> data = malloc(capacity*elem_size);
	if(!q->data){
		free(q);
		return NULL;
	}
	return q;
}

void queue_dispose(struct Queue *q){
	if(q){
		free(q->data);
		free(q);
	}
}

static void enlarge_queue_capacity(struct Queue *q);

void queue_enqueue(struct Queue *q, const void *src){
	if (q->length==q->capacity){
		enlarge_queue_capacity(q);
	}
	size_t pos = (q->front + q-> length) % q->capacity;
	memcpy((char*)q->data + pos*q->elem_size,src,q->elem_size);
	q->length++;
}

void queue_dequeue(struct Queue *q, void *dest){
	if(is_empty(q)){
		printf("Queue is empty\n");
	} else {
		q->front = (q->front + 1) % q->capacity;
		q->length -= 1;
	}
}

static void enlarge_queue_capacity(struct Queue *q){
	if(q->length < q->capacity) return;
	size_t new_capacity = q->capacity*2;
	void *new_data = malloc(new_capacity*q -> elem_size);
	if(!new_data) return;
	for(size_t i=0; i < q->length; i++){
		
		size_t pos = (q->front +i) % q->capacity;
		memcpy((char*)new_data + i *q -> elem_size, 
			(char*)q->data+pos*q->elem_size,q->elem_size);
		
		}
		
		free(q->data);
		q->data = new_data;
		q->capacity = new_capacity;
		q->front=0;
}


