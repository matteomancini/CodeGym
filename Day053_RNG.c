#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#define N 2147483647
#define G 16807

void lehmer (uint32_t *s){
   uint32_t d = *s / (N / G);
   uint32_t r = *s % (N / G);
   uint32_t a = r * G;
   uint32_t b = d * (N % G);
   *s = a > b ? a - b : a + N - b;
}

int main (int argc, char *argv[]){
   int i = 0, n = 10;
   char *endptr;
   uint32_t r = (uint32_t )(time (0));

   if (argc > 1){
      n = strtol (argv[1], &endptr, 10);
      if (! *argv[1] || *endptr)
         return (1);
   }

   for (i = 0; i < n; i++){
      lehmer (&r);
      printf ("%d\t", r % 100);
   }
   printf ("\n");
   return (0);
}
