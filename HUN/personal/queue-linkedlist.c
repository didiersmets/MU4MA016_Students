
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *connect;
  int data;
} Node ;

typedef struct Queue{
  struct Node *head;
  struct Node *tail;
  int length;
} Queue;


Queue *initQ();
void killQ(Queue *q);
void pushQ(Queue *q, int x);
void popQ(Queue *q);




Queue *initQ() {
  Queue *q = malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  q->length = 0;
  return q;
}


void pushQ(Queue *q, int data) {
  Node *new = malloc(sizeof(Node));
  new->data = data;
  new->connect = NULL;

  if (q->length == 0){
    q->head = new;
    q->tail = new;
  }

  q->tail->connect = new;
  q->tail = new;
  q->length++;
}

void popQ(Queue *q) {
  if (q->length == 0){
    fprintf(stderr,"Error: Cannot dequeue an empty queue.\n");
    exit(1);
  }
  Node *newHead = q->head->connect;
  free(q->head);
  q->head = newHead;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


int main() {

  Queue *q = initQ();
  pushQ(q, 3);
  pushQ(q, 6);
  printf("------------------\n");
  popQ(q);
  popQ(q);


  return 0;
}
