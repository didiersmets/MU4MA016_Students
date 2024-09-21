
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


typedef struct Node {
  struct Node *next;
  int data;
} Node;

typedef struct Stack {
  struct Node *head; 
} Stack;

Stack* stackNew();
void stackPush(Stack *s, int n);
void stackPop(Stack *s);
void stackPeek(Stack *s);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Stack* stackNew() {
  Stack *s = malloc(sizeof(Stack));
  s->head = NULL;
  return s;
}

void stackPush(Stack *s, int n) {
  Node *newhead = malloc(sizeof(Node));
  newhead->data = n;
  newhead->next = s->head;
  s->head = newhead;
  printf("%d\n", s->head->data);
}

void stackPop(Stack *s) {
  if (s->head==NULL){
    fprintf(stderr, "Error: Operation `pop` cannot operate on empty Stack.\n");
    exit(1);
  }
  Node *newhead = s->head->next;
  free(s->head);
  s->head = newhead;
}

void stackPeek(Stack *s) {
  if (s->head == NULL){
    fprintf(stderr, "Error: Cannot peek a Stack whose head is empty.\n");
    exit(1);
  }
  printf("Current head: %d\n", s->head->data);
}




int main(){

  Stack *x = stackNew();
  stackPush(x, 3);
  stackPush(x, 5);
  stackPush(x, 9);
  printf("--------\n");
  stackPop(x);
  stackPop(x);
  stackPop(x);
  stackPeek(x);
  return 0;
}
