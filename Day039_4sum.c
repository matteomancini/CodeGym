#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 50

typedef struct{
   int x;
   int y;
   int sum;
} partsum;

int pscmp (const void *x, const void *y){
   return ((*(partsum *)x).sum - (*(partsum *)y).sum);
}

int shared (partsum p1, partsum p2){
   return (p1.x == p2.x || p1.x == p2.y || p1.y == p2.x || p1.y == p2.y);
}

void zerosum (int *data, int len){
   int i, j, k = 0, n = (len * (len - 1)) / 2;
   partsum *p = malloc ((n * sizeof(partsum)));
   for (i = 0; i < len; i++)
      for (j = i + 1; j < len; j++){
         p[k].x = i;
         p[k].y = j;
         p[k++].sum = data[i] + data[j];
      }

   qsort (p, n, sizeof(partsum), pscmp);

   for (i = 0; i < n - 1; i++)
      for (j = i + 1; j < n; j++)
         if ((p[i].sum + p[j].sum) == 0 && !shared(p[i], p[j]))
            printf ("(%d, %d, %d, %d)\n",
               data[p[i].x], data[p[i].y], data[p[j].x], data[p[j].y]);
}

int main (int argc, char *argv[]){
   int *d, n, i;
   char *endptr;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else if (argc > MAX_LEN+1){
      printf ("Too many arguments\n");
      return (1);
   }
   else{
      n = argc - 1;
      d = malloc (n * sizeof(int));
      for (i = 0; i < n; i++){
         d[i] = strtol (argv[i+1], &endptr, 10);
         if (! argv[i+1] || *endptr){
            printf ("Invalid character: %s\n", argv[i+1]);
            return (1);
         }
      }
   }

   zerosum (d, n);

   return (0);
}

