#include <stdio.h>
#include <stdlib.h>
#define N 4
#define TOL 0.00000001

double* mvmult (double A[][N], double *v){
   int i, j;
   double *r = calloc (N, sizeof(double));
   for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
         r[i] += A[i][j] * v[j];
   return (r);
}

double* diff (double *v, double *w, int n){
   double *d = malloc (n * sizeof(double));
   int i;
   for (i = 0; i < n; i++)
      d[i] = v[i] - w[i];
   return (d);
}

double scal (double *v, double *w, int n){
   double r = 0;
   int i;
   for (i = 0; i < n; i++)
      r += v[i] * w[i];
   return (r);
} 

double* deg (double G[][N]){
   double *d = calloc (N, sizeof(double));
   int i, j;
   for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
         d[i] += G[i][j];
   return (d);
}

void teleports (double G[][N], double alpha){
   int i, j;
   double *d = deg (G);
   for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
         G[i][j] = alpha * G[i][j] / d[j] + (1-alpha) / N;
}

double* pagerank (double G[][N], double alpha){
   double *p, *r;
   int i;
   teleports (G, alpha);
   p = calloc (N, sizeof(double));
   r = malloc (N * sizeof(double));
   for (i = 0; i < N; i++)
      r[i] = (double) 1/N;
   while (scal(diff(r, p, N), diff(r, p, N), N) > TOL){
      p = r;
      r = mvmult (G, p);
   }
   return (r);
}

int main (){
   double graph[][N] = {{0, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 0}};
   double *pr;
   int i;
   pr = pagerank (graph, 0.9);
   for (i = 0; i < N; i++)
      printf("%f\t", pr[i]);
   printf ("\n");
   return (0);
}

