#include <stdio.h>
#include <stdlib.h>

void swap (int *x, int *y){
   int tmp = *x;
   *x = *y;
   *y = tmp;
}

int gcd (int x, int y, int *u, int *v){
   int tmp, q, u_ = 0, v_ = 1;
   *u = 1;
   *v = 0;
   while (y){
      q = x / y;
      swap (u, &u_);
      u_ = u_ - q * (*u);
      swap (v, &v_);
      v_ = v_ -q * (*v);
      swap (&x, &y);
      y = y % x;
   }
   return (x);
}

int main (int argc, char *argv[]){
   int x, y, u, v;
   char *endptr;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      x = strtol (argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         printf ("Invalid number: %c\n", *argv[1]);
         return (1);
      }
      y = strtol (argv[2], &endptr, 10);
      if (! argv[2] || *endptr){
         printf ("Invalid number: %c\n", *argv[2]);
         return (1);
      }
   }

   x = gcd (x, y, &u, &v);

   printf ("%d\t %d\t %d\n", x, u, v);
   return (0);
}

