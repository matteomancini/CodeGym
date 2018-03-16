#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

typedef struct {
   int res[N];
   int k;
} sampler;

void init_samp (sampler *s){
   s->k = 0;
}

void rs (sampler *s, int n, int i){
   int j;
   if (s->k < N)
      s->res[(s->k)++] = n;
   else{
      srand (time(NULL));
      j = rand() % (i+1);
      if (j < s->k)
         s->res[j] = n;
   }
}

int main (int argc, char *argv[]){
   sampler s;
   int i, n;
   char *endptr;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      init_samp (&s);
      for (i = 1; i < argc; i++){
         n = strtol (argv[i], &endptr, 10);
         if (! *argv[i] || *endptr)
            printf ("Invalid number: %c\n", argv[i]);
         rs (&s, n, i);
      }
   }
   for (i = 0; i < s.k; i++)
      printf("%d, ", s.res[i]);
   printf("\n");
   return (0);
}

