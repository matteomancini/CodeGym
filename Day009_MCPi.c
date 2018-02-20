#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BATCH 1000

double qrand(){
   double x = (double )(rand()) / RAND_MAX;
   return (x * x);
}

double pi (long n){
   double t;
   for (int i = 0; i < n/BATCH; i++)
      for (int j = 0; j < BATCH; j++)
         t += ((qrand()+qrand()) <= 1);
   return (4 * t / n);
}

int main (int argc, char *argv[]){
   long n;
   double p;
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
   srand (time(0));
   p = pi (n);
   printf ("%f\n", p);
   return (0);
}

