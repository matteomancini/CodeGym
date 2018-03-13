#include <stdio.h>
#include <stdlib.h>

double** strassen2x2 (double a[][2], double b[][2]){
   double t[7], **c;
   int i, n = 2;
   c = malloc (n * sizeof(double));
   for (i = 0; i < n; i++)
      c[i] = malloc (n * sizeof(double));
   t[0] = (a[0][0] + a[1][1])*(b[0][0] + b[1][1]);
   t[1] = (a[1][0] + a[1][1])*b[0][0];
   t[2] = a[0][0]*(b[0][1] - b[1][1]);
   t[3] = a[1][1]*(b[1][0] - b[0][0]);
   t[4] = (a[0][0] + a[0][1])*b[1][1];
   t[5] = (a[1][0] - a[0][0])*(b[0][0] + b[0][1]);
   t[6] = (a[0][1] - a[1][1])*(b[1][0] + b[1][1]);

   c[0][0] = t[0] + t[3] - t[4] + t[6];
   c[0][1] = t[2] + t[4];
   c[1][0] = t[1] + t[3];
   c[1][1] = t[0] - t[1] + t[2] + t[5];
   return (c);
}

int main (){
   double a[][2] = {{1, 2}, {3, 4}};
   double b[][2] = {{5, 6}, {7, 8}};
   double **c;
   int i, j, n = 2;

   c = strassen2x2 (a, b);
   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++)
         printf ("%f\t", c[i][j]);
      printf ("\n");
   }
   return (0);
}
