#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NPTS 4

int fact (int n){
   if (n >= 1)
      return (n * fact(n-1));
   else
      return (1);
}

int comb (int n, int k){
   return (fact(n) / (fact(k) * fact(n - k)));
}

void vecmatmul (double *a, double b[][2], int n, double **c){
   int i, j;
   for (i = 0; i < n; i++){
      (*c)[0] += a[i] * b[i][0];
      (*c)[1] += a[i] * b[i][1];
   }
}

double **bezier (double pts[][2], int n, int nsteps){
   double t;
   double **points = calloc (nsteps, sizeof (double *));
   double *u = calloc (nsteps, sizeof (double));
   int i, r;
   int *b = calloc (n, sizeof(int));
   for (i = 0; i < nsteps; i++)
      points[i] = calloc (2, sizeof (double));
   for (i = 0; i < n; i++)
      b[i] = comb (n - 1, i);
   for (i = 0; i < nsteps; i++){
      t = (double )(i) / nsteps;
      for (r = 0; r < n; r++)
         u[r] = b[r] * pow(t, r) * pow (1 - t, n - r -1);
      vecmatmul (u, pts, n, &(points[i]));
   }
   return (points);
}

int main (){
   double points[NPTS][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
   double **bp;
   int i;
   bp = bezier (points, NPTS, 100);
   for (i = 0; i < 100; i++)
      printf("%.6f\t%.6f\n", bp[i][0], bp[i][1]);
   return (0);
}
