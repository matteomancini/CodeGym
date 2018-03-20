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
   for (i = n - 1; i > 0; i--){
      j = rand() % (i + 1);
      swap(&d[i], &d[j]);
   }
}

int* part (int *d, int s, int p, int *n, int *k){
   int i, m = 0, *h = malloc ((*n) * sizeof(int));
   for (i = 0; i < *n; i++)
      if (*k < s){
         if (d[i] <= d[p])
            h[m++] = d[i];
      }
      else{
         if (d[i] > d[p])
            h[m++] = d[i];
      }

   *n = m;
   *k = *k < s ? *k : *k - s;
   return (h);
}

int kth (int *data, int n, int k){
   if (n==1)
      return (data[0]);

   int p = rand() % n;
   int *d, i, split = 0;
   for (i = 0; i < n; i++)
      if (data[i] <= data[p])
         split += 1;
   d = part (data, split, p, &n, &k);

   return (kth (d, n, k));
}

int main (int argc, char *argv[]){
   int i, n, k, *a;
   char *endptr;
   if (argc < 3){
      n = 100;
      k = 50;
   }
   else{
      n = strtol (argv[1], &endptr, 10);
      if (! *argv[1] || *endptr){
         printf ("Invalid number: %s\n", argv[1]);
         return (1);
      }
      k = strtol (argv[2], &endptr, 10);
      if (! *argv[2] || *endptr){
         printf ("Invalid number: %s\n", argv[2]);
         return (1);
      }      
   }
   a = malloc (n * sizeof(int));
   for (i = 0; i < n; i++)
      a[i] = i;
   srand (time(NULL));
   shuffle (a, n);
   printf ("%d\n", kth(&a[0], n, k));
   return (0);
}

