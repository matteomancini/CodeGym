#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int b;
   int c;
} score;

score getscore (int *x, int *y, int n){
   score s;
   int i, j;
   s.b = 0;
   s.c = 0;
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         if (x[i] == y[j])
            if (i == j)
               s.b += 1;
            else
               s.c += 1;
   return s;
}

score p1 (int *secret, int *tip, int n){
   return (getscore (secret, tip, n));
}

int* generate (int n){
   int i, r, *d = 0;
   int dec[10] = {0};
   if (n < 10){
      d = malloc (n * sizeof(int));
      for (i = 0; i < n; i++){
         r = rand() % 10;
         while (dec[r] == 1)
            r = rand() % 10;
         d[i] = r;
         dec[i] = 1;
      }
   }
   return (d);
}

int main (){
   score s;
   int *secret, *guess, i, k = 0, n = 4;
   s.b = 0;
   srand (time(NULL));
   secret = generate (n);
   while (s.b < n){
      guess = generate (n);
      printf ("Guess: ");
      for (i = 0; i < n; i++)
         printf ("%d", guess[i]);
      s = p1 (secret, guess, n);
      printf(" - %d bulls and %d cows\n", s.b, s.c);
      k++;
   }
   printf("Secret: ");
   for (i = 0; i < n; i++)
      printf ("%d", secret[i]);
   printf (" - Player One won (%d attempts).\n", k);
   return (0);
}

