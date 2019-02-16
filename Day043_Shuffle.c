#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap (int *x, int *y){
   int tmp = *x;
   *x = *y;
   *y = tmp;
}

void shuffle (int *d, int n){
   int i, j;
   for (i = 0; i < n; i++){
      j = (rand() % (n-i)) + i;
      swap(&d[i], &d[j]);
   }
}

void print_array (int *a, int n){
   int i;
   for (i = 0; i < n; i++)
      printf ("%d ", a[i]);
   printf ("\n");
}

int main (int argc, char *argv[]){
   int i, n, *d;
   char *endptr;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      n = strtol (argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         printf ("Invalid character: %s\n", argv[1]);
         return (1);
      }
   }
   srand (time(NULL));
   d = malloc (n * sizeof(int));
   for (i = 0; i < n; i++)
      d[i] = i;
   for (i = 0; i < n; i++){
      shuffle (d, n);
      print_array (d, n);
   }
   return (0);
}

