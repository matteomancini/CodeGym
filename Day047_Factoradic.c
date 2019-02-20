#include <stdio.h>
#include <stdlib.h>

struct list{
   int d;
   struct list *n;
};

int fact (int n){
   if (n > 1)
      return (n * fact(n - 1));
   else
      return (1);
}

void fac (struct list **f, int x, int i){
   if (x != 0){
      (*f) = malloc (sizeof(struct list));
      (*f)->d = x % i;
      fac (&((*f)->n), x / i, i + 1);
   }
}

int dec (struct list *f, int i){
   if (f != NULL)
      return ((f->d) * fact (i) + dec (f->n, i + 1));
   else
      return (0);
}

int main (int argc, char *argv[]){
   int x, i = 1, pseudof = 0, d = 0;
   struct list *f, *n;
   char *endptr;

   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      x = strtol (argv[1], &endptr, 10);
      if (! *argv[1] || *endptr)
         return (1);
   }

   fac (&f, x, i);
   n = f;
   while (n != NULL){
      pseudof += n->d * i;
      n = n->n;
      i *= 10;
   }

   i = 0;
   d = dec (f, i);
   printf ("%d(fac) <-> %d(dec)\n", pseudof, d);
   return (0);
}
