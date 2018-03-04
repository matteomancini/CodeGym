#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newrap (double x, double y, double p){
   double yp = y;
   y = y * (2-y*x);
   while (fabs(y-yp) > p){
      yp = y;
      y = y * (2-y*x);
   }
   return (y);
}

int main (int argc, char *argv[]){
   double x, y;
   char *endptr;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      x = strtod (argv[1], &endptr);
      if (! argv[1] || *endptr){
         printf ("Invalid number: %c\n", argv[1]);
         return (1);
      }
      y = strtod (argv[2], &endptr);
      if (! argv[2] || *endptr){
         printf ("Invalid number: %c\n", argv[2]);
         return (1);
      }
   }
   printf ("%f - Estimated: %f\n", 1/x, newrap(x, y, 0.001));
   return (0);
}

