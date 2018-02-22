#include <stdio.h>
#include <stdlib.h>

int mccarthy91 (int n){
   int k = 1;
   while (k){
      if (n > 100){
         n = n - 10;
         k -= 1;
      }
      else{
         n += 11;
         k += 1;
      }
   }
   return (n);
}

int mccarthy91r (int n){
   if (n > 100)
      return (n - 10);
   else
      return (mccarthy91r(mccarthy91r(n+11)));
}

int main (int argc, char *argv[]){
   int n;
   char *endptr;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      n = strtol (argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         printf ("Invalid number: %s\n", argv[1]);
         return (1);
      }
   }
   printf ("%d\n", mccarthy91r(n));
   return (0);
}

