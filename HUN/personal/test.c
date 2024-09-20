#include<stdlib.h>

typedef struct {} stack;

stack *stackNew();
void stackPsuh();
int stackPop();
void stackFini();

/* ================================================== */

typedef struct {
  struct stackNode *next;
  int data;
} stackNode ;

struct stack {
  stackNode *head;
};

stack *stackNew() {
  stack *s = malloc(sizeof(stack));
  s->head = NULL;
  return s;
}




/* ================================================== */

int main() {

  return 0;
}
