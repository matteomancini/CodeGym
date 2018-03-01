#include <stdio.h>
#include <stdlib.h>

double next_probability (double *p, int i){
   double s;
   for (int k = i - 6; k < i; k++)
      s += p[k];
   return (s/6);
}

int main (int argc, char *argv[]){
   int n, i;
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
   double *p = calloc ((n+6), sizeof(double));
   p[5] = 1;
   for (i = 6; i < n + 6; i++){
      p[i] = next_probability (p, i);
      printf ("%f ", p[i]);
   }
   printf ("\n"); 
   return (0);
}

