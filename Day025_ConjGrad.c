#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCOL 3
#define TOL 0.0001

void mvmult (double A[][NCOL], int n, double *v, double **r){
   int i, j;
   (*r) = calloc (n, sizeof(double));
   for (i = 0; i < n; i++)
      for (j = 0; j < NCOL; j++)
         (*r)[i] += A[i][j]*v[j];
}

void sumvec (double *v, double *w, int n, double s, double *r){
   int i;
   for (i = 0; i < n; i++){
      r[i] = w[i] * s;
      if (v!=w)
         r[i] += v[i];
   }
}

double scal (double *v, double *w, int n){
   double r = 0;
   int i;
   for (i = 0; i < n; i++)
      r += v[i] * w[i];
   return (r);
} 

void cgrad (double A[][NCOL], int n, double *b, double *x){
   double *res, *dir, *Adir, err, err_;
   mvmult (A, n, x, &res);
   sumvec (b, res, n, -1, res);
   dir = malloc (n * sizeof(double));
   memcpy (dir, res, n * sizeof(double));
   err = scal (res, res, n);
   while (err > TOL){
      mvmult (A, n, dir, &Adir);
      sumvec (x, dir, n, err / scal(dir,Adir,n), Adir);
      memcpy (x, Adir, n * sizeof(double));
      mvmult (A, n, x, &res);
      sumvec (b, res, n, -1, res);
      err_ = err;
      err = scal (res, res, n);
      sumvec (res, dir, n, err / err_, dir);
   }
}

int main (int argc, char *argv[]){
   int i, n = 3;
   double A[][NCOL] = {{1,2,3}, {4,5,6}, {7,8,9}};
   double b[] = {1, 2, 3};
   double *r = malloc (n * sizeof(double));
   cgrad (A, n, b, r);
   for (i = 0; i < n; i++)
      printf ("%f\n", r[i]);
   return (0);
}
