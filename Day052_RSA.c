#include <stdio.h>
#include <stdlib.h>
#define E_CONST 65537
#define PRIME_1 7937
#define PRIME_2 6673

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

long long modinv (long long x, long long y, long long t){
   long long r = 1, s = 0, aux;
   while (y){
      aux = r;
      r = s;
      s = aux - (x / y) * s;
      aux = x;
      x = y;
      y = aux % y;
   }
   r = r % t;
   return ((r < 0) ? r + t : r);
}

long long **rsa_keygen (){
   long long n, t, d, **keys;
   n = PRIME_1 * PRIME_2;
   t = n - PRIME_1 - PRIME_2 + 1;
   d = modinv (E_CONST, t, t);
   keys = calloc (2, sizeof (long long *));
   keys[0] = calloc (2, sizeof (long long));
   keys[1] = calloc (2, sizeof (long long));
   keys[0][0] = E_CONST;
   keys[0][1] = n;
   keys[1][0] = d;
   keys[1][1] = n;
   return (keys);
}

long long rsa (long long t, long long *key){
   return (powmod (t, key[0], key[1]));
}

int main (int argc, char *argv[]){
   long long n, c, **k;
   char *endptr;

   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      n = strtoll (argv[1], &endptr, 10);
      if (! *argv[1] || *endptr)
         return (1);
   }

   k = rsa_keygen ();
   c = rsa (n, k[0]);
   printf("Crypted: %d\nUncrypted: %d\n", c, rsa (c, k[1]));
   return (0);
}
