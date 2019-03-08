#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 24
#define NTESTS 32

long long powmod (long long b, long long e, long long d){
   long long p = 1;
   b = b % d;
   while (e > 0){
      if (e & 1)
         p = (p * b) % d;
      e = e >> 1;
      b = (b * b) % d;
   }
   return (p);
}

long long rabin_miller (long long p, int t){
   long long q = p - 1, r = 0, n, x;
   int i, j;
   if (p < 5)
      return (p == 2 || p == 3);

   while (!(q & 1)){
      q >>= 1;
      r += 1;
   }

   for (i = 0; i < t; i++){
      n = 2 + (rand() % (p - 3));
      x = powmod (n, q, p);
      if (x == 1 || x == (p - 1))
         continue;

      for (j = 0; j < r - 1; j++){
         x = powmod (x, 2, p);
         if (x == (p - 1))
            break;
      }
      if (j == (r - 1))
         return (0);
   }

   return (1);
}

long long prime (long long b, int t){
   long long p;
   srand (time(0));
   while (1){
      p = (1 << b) | rand() % (1 << b) | 1;
      if (rabin_miller (p, t))
         return (p);
   }
}

int main (){
   printf ("%d\n", prime (LEN, NTESTS));
   return (0);
}
