#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct {
  int size;
  int data[MAX_SIZE];
} stack;

void stack_init (stack *s){
  s->size = 0;
}

int stack_push (stack *s, int d){
  s->data[s->size++] = d;
}

int stack_pop(stack *s){
  int d;
  if (s->size > 0){
    d = s->data[--(s->size)];
    s->data[s->size] = 0;
    return (d);
  }
  else
    return (0);
}

void move(int n, stack *src, stack *trg, stack *aux){
  int d;
  if (n > 0){
    move (n - 1, src, aux, trg);
    d = stack_pop (src);
    stack_push (trg, d);
    move (n - 1, aux, trg, src);
  }
}

void plot_stacks(int n, stack *s1, stack *s2, stack *s3){
  for (int i = n - 1; i >= 0; i--)
    printf("%d\t%d\t%d\n", s1->data[i], s2->data[i], s3->data[i]);
}

int main(int argc, char *argv[]){
  int n;
  char *endptr;
  stack *left = (stack*) calloc (1, sizeof(stack));
  stack *mid = (stack*) calloc (1, sizeof(stack));
  stack *right = (stack*) calloc (1, sizeof(stack));

  if (argc < 2)
    n = 3;
  else{
    n = strtol (argv[1], &endptr, 10);
    if (! *argv[1] || *endptr){
      printf ("Invalid number: %c\n", argv[1]);
      return (1);
    }
    else if (n > 9)
      n = 3;
  }
  printf ("n = %d\n", n);

  stack_init (left);
  stack_init (mid);
  stack_init (right);

  for (int i = n; i > 0; i--){
    stack_push (left, i);
  }

  printf ("Stacks initialized\n");
  plot_stacks (n, left, mid, right);

  move (n, left, right, mid);

  printf ("\nStacks sorted!\n");
  plot_stacks (n, left, mid, right);

  return (0);
}
