#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 7

int intpow (int b, int e){
   int p = 1;
   while (e > 0){
      p *= b;
      e--;
   }
   return (p);
}

int is2pow (int n){
   if (n == 0)
      return (0);
   while (n != 1){
      if (n % 2 != 0)
         return (0);
      n /= 2;
   }
   return (1);
}

int *encode (int *data, int n){
   int i, j, c, p, len, *code;
   p = ceil (log2(n)) + 1;
   len = n + p;
   code = calloc (len, sizeof(int));

   c = 0;
   for (i = 0; i < len; i++)
      if (!(is2pow(len - i))){
         code[i] = data[c];
         c++;
      }
      else
         code[i] = 0;

   for (i = 1; i <= p; i++)
      for (j = intpow(2, i-1) + 1; j <= len; j++)
         if (j & intpow(2, i-1))
            code[len - intpow(2, i-1)] ^= code[len - j];

   return (code);
}

int *error_check (int *code, int n, int l){
   int i, j, p, *c;
   p = l - n;
   c = calloc (p, sizeof(int));
   for (i = 1; i <= p; i++){
      c[i - 1] = code[l - intpow(2, i-1)];
      for (j = intpow(2, i-1) + 1; j <= l; j++)
         if (j & intpow(2, i-1))
            c[i - 1] ^= code[l - j];
   }
   return (c);
}

int main (){
   int data[SIZE] = {1, 0, 1, 1, 0, 0, 1};
   int i, l, sim, *code, *err;
   code = encode(data, SIZE);
   l = SIZE + ceil (log2(SIZE)) + 1;
   printf ("Encoded data: ");
   for (i = 0; i < l; i++)
      printf ("%d ", code[i]);
   printf ("\n");

   sim = 5;
   code[sim] = code[sim] == 1 ? 0 : 1;
   err = error_check (code, SIZE, l);
   printf ("Simulated error at position: ");
   for (i = 0; i < l - SIZE; i++)
      printf ("%d ", err[i]);
   printf ("\n");

   return (0);
}
