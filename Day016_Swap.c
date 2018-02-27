#include <stdio.h>
#include <stdlib.h>

void swap_add (int *x, int *y){
   *x = *x + *y;
   *y = *x - *y;
   *x = *x - *y;
}

void swap_xor (int *x, int *y){
   *x = *x ^ *y;
   *y = *x ^ *y;
   *x = *x ^ *y;
}

int main (int argc, char *argv[]){
   int a, b;
   char *endptr;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      a = strtol (argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         return (1);
      }
      b = strtol (argv[2], &endptr, 10);
      if (! argv[2] || *endptr){
         return (1);
      }
   }
   swap_xor (&a, &b);
   printf ("%d\t%d\n", a, b);
   swap_add (&a, &b);
   printf ("%d\t%d\n", a, b);

   return (0);
}

