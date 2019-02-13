#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 3

typedef struct {
   int size;
   int data[MAX_SIZE];
} tail;

struct counter {
   struct counter *n;
   tail *d;
};

void tail_init (tail *t){
   t->size = 0;
}

void tail_push (tail *t, int d){
   t->data[t->size++] = d;
}

int tail_size (tail *t){
   return (t->size);
}

int tail_pop (tail *t){
   int d, i;
   if (tail_size(t) > 0){
      d = t->data[0];
      for (i = 1; i < tail_size(t); i++)
         t->data[i-1] = t->data[i];
      t->data[--t->size] = 0;
      return (d);
   }
   else
      return (0);
}

void print_tail (tail *t){
   int i;
   for (i = 0; i < tail_size(t); i++)
      printf ("%d\t", t->data[i]);
   printf("\n");
}

void update (struct counter *c, int timestamp){
   int latest;
   struct counter *next;
   tail_push (c->d, timestamp);
   while (tail_size (c->d) == 3){
      tail_pop (c->d);
      latest = tail_pop (c->d);
      if (c->n == NULL){
         next = calloc (1, sizeof(struct counter));
         next->d = calloc (1, sizeof(tail));
         tail_init (next->d);
         c->n = next;
      }
      c = c->n;
      tail_push (c->d, latest);
   }
}

void count (struct counter *c, int n, int *timestamp){
   if (n == 1)
      update (c, ++(*timestamp));
   else
      (*timestamp)++;
}

int estimate (struct counter *c, int n){
   int i, w = 1, k = 0, est = 0;
   tail *t;
   while (c != NULL){
      t = c->d;
      for (i = 0; i < tail_size(t); i++)
         if (t->data[i] > n){
            k = w;
            est += k;
         }
      c = c->n;
      w *= 2;
   }
   est -= k / 2;
   return (est);
}

struct counter *init_count (int *timestamp){
   *timestamp = 0;
   struct counter *c = calloc (1, sizeof(struct counter));
   c->d = calloc (1, sizeof(tail));
   tail_init (c->d);
   return (c);
}

void print_counter (struct counter *c){
   int i, n = 1;
   while (c != NULL){
      printf ("%d - ", n);
      print_tail (c->d);
      n *= 2;
      c = c->n;
   }
}

int main (){
   int len = 1000, i, n, k = 900, id;
   struct counter *c = init_count (&id);
   srand (time(NULL));
   for (i = 0; i < len; i++){
      n = rand() % 2;
      count (c, n, &id);
   }
   printf ("Last %d elements: %d\n", len - k, estimate(c, k));
   return (0);
}
