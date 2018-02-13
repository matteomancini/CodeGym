#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_sqmat(int **mat, int n){
   for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++)
         printf ("%d\t", mat[i][j]);
      printf ("\n");
   }
}

int mcm (int *dims, int nd){
   int n = nd - 1;
   int i, j, k, len, m;
   int **mul;

   mul = calloc (n, sizeof(int*));
   for (i = 0; i < n; i++)
      mul[i] = calloc (n, sizeof(int));

   for (len = 1; len < n; len++){
      for (i = 0; i < n-len; i++){
         j = i + len;
         mul[i][j] = INT_MAX;
         for (k = i; k < j; k++){
            m = mul[i][k] + mul[k+1][j] + dims[i]*dims[k+1]*dims[j+1];
            if (m < mul[i][j]){
               mul[i][j] = m;
               mul[j][i] = k+1;
            }
         }
      }
   }

   print_sqmat (mul, n);

   return (mul[0][n-1]);
}

int main(int argc, char *argv[]){
   int *mat_dims;
   int n, min_mul;
   char *endptr;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      n = argc - 1;
      mat_dims = calloc (n, sizeof(int));
      for(int a = 0; a < n; a++){
         mat_dims[a] = strtol (argv[a+1], &endptr, 10);
         if (! argv[a+1] || *endptr){
            printf ("Invalid input: %c\n", argv[a+1]);
            return (1);
         }
      }
   }

   min_mul = mcm (mat_dims, n);

   printf ("\nThe minimum number of multiplications is %d\n", min_mul);

   return (0);
}
