#include <stdio.h>
#include <stdlib.h>

void print_bin (int n){
   if ((n/2) == 0){
      printf ("%d", n);
   }
   else{
      print_bin (n / 2);
      printf ("%d", n % 2);
   }
}

int count_ones (int n){
   int k = 0;
   while (n > 0){
      n &= n-1;
      k++;
   }
   return k;
}

int main (int argc, char *argv[]){
   int n;
   int ones;
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

   printf ("Binary representation: ");
   print_bin (n);
   ones = count_ones (n);
   printf ("\nNumber of bits equal to one: %d\n", ones);
   return (0);
}

