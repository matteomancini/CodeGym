#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 3

void matgauss (double **mat, int n, int k){
   double **m = calloc (n, sizeof(double*));
   int i, j;
   for (i = 0; i < n; i++)
      m[i] = calloc (n, sizeof(double));
   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
         m[i][j] = mat[i][j] - mat[i][0] * (mat[k][j]/mat[k][0]);
      }
   }
   for (i=0; i<n; i++)
      mat[i] = m[i];
}

void removerow (double **mat, int n, int k){
   int i;
   n--;
   free (mat[k]);
   for (i = k; i < n; i++)
      mat[i] = mat[i+1];
}

void removecol (double **mat, int n, int k){
   int i, j;
   n--;
   for (i = 0; i < n+1; i++){
      for (j = k; j < n; j++)
         mat[i][j] = mat[i][j+1];
      mat[i] = realloc (mat[i], sizeof(double)*n);
   }
}

double det (double **mat, int n){
   if (n==1)
      return (mat[0][0]);

   int i, k = 0;
   double p;

   for (i = 0; i < n; i++)
      if (mat[i][0] > mat[k][0])
         k = i;
   p = mat[k][0];

   matgauss (mat, n, k);

   removerow (mat, n, k);
   removecol (mat, n, 0);

   return (p * pow(-1,(k%2)) * det(mat, n-1));
}

int main (int argc, char *argv[]){
   double d, mat[SIZE][SIZE] = {{4, 9, 2},
      {3, 5, 7},
      {8, 1, 6}
   };
   int i, j;
   double **m = malloc (SIZE*sizeof(double*));
   for (i = 0; i < SIZE; i++){
         m[i] = malloc (SIZE*sizeof(double*));
      for (j = 0; j < SIZE; j++)
         m[i][j] = mat[i][j];
   }
   d = det (m, SIZE);
   printf("%f\n", d);
   return (0);
}

