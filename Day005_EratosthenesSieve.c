#include <stdio.h>
#include <stdlib.h>

int era (long n){
   long i;
   long j = 3;
   int np = 0;
   short *p;
   n = (n+1) >> 1;
   p = calloc(n, sizeof(short));
   for (i = 1; i < n; i++){
      if (p[i] == 0)
         for (long k=j*j >> 1; k < n; k += j)
            p[k] = 1;
      j += 2;
   }
   for (i = 0; i < n; i++)
      np = np + !p[i];
   return (np);
}

int main (int argc, char *argv[]){
   long n;
   int p = 0;
   char *endptr;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      n = strtol (argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         printf ("Invalid number: %c\n", argv[1]);
         return (1);
      }
   }
   if (n > 1)
      p = era (n);
   printf ("Number of prime numbers: %d\n", p);
   return (0);
}

