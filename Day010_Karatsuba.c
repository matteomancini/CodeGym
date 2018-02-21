#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void half (long n, int m, long *a, long *b){
   *a = n / pow (10, m);
   *b = n - *a * pow (10, m);
}

long karatsuba (long x, long y){
   long a, b, c, d;
   long ac, bd, abcd;
   int m = log10 (x) / 2;

   if (m == 0)
      return (x*y);

   half (x, m, &a, &b);
   half (y, m, &c, &d);

   ac = karatsuba (a, c);
   bd = karatsuba (b, d);
   abcd = karatsuba (a+b, c+d);

   return (ac*pow(10,2*m)+bd+(abcd-ac-bd)*pow(10,m));
}

int main (int argc, char *argv[]){
   long a, b, c;
   char *endptr;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      a = strtol(argv[1], &endptr, 10);
      if (! argv[1] || *endptr){
         printf ("Invalid number: %c\n", argv[1]);
         return (1);
      }
      b=strtol(argv[2], &endptr, 10);
      if (! argv[2] || *endptr){
         printf ("Invalid number: %c\n", argv[2]);
         return (1);
      }
      if ((int )(log10(a)) != (int )(log10(b))){
         printf ("Numbers with the same numbers of digit needed\n");
         return (1);
      }
   }
   c = karatsuba (a, b);
   printf ("%d\n", c);
   return (0);
}

