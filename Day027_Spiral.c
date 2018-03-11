#include <stdio.h>
#include <stdlib.h>

int spiral(int x, int y, int i, int j)
{
   if (j==0)
      return (i);

	return (x + spiral (--y, x, --j, x-i-1));
}

int main (int argc, char *argv[]){
   int i, j, n;
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
   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++)
         printf ("%d\t", spiral (n, n, j, i));
      printf ("\n");
   }
   return (0);
}

