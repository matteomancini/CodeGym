#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define NPTS 9
#define TOL 0.001

typedef struct {
   double x;
   double y;
} point;

double distance (point *p, int n, point *c, int k, int *h){
   double cumdis = 0;
   double sqrs;
   int i, j, min;
   for (i = 0; i < n; i++){
      min = INT_MAX;
      for (j = 0; j < k; j++){
         sqrs = pow (p[i].x - c[j].x, 2) + pow(p[i].y - c[j].y, 2);
         cumdis += sqrt (sqrs);
         if (sqrt(sqrs) < min){
            min = sqrt(sqrs);
            h[i] = j;
         }
      }
   }
   return cumdis;
}

void update (point *ctr, int k, point *pts, int n, int *cls){
   int i, j, *nk = calloc(k, sizeof(int));
   for (j = 0; j < k; j++){
      ctr[j].x = 0;
      ctr[j].y = 0;
   }
   for (i = 0; i < n; i++){
      ctr[cls[i]].x += pts[i].x;
      ctr[cls[i]].y += pts[i].y;
      nk[cls[i]]++;
   }
   for (j = 0; j < k; j++){
      ctr[j].x /= nk[j];
      ctr[j].y /= nk[j];
   }
}

int* kmeans (point *pts, int n, int k){
   int *kmeans = malloc (n*sizeof(int));
   int i, *clusters = calloc (n, sizeof(int));
   point *ctr = malloc (k*sizeof(point));
   double d, curloss = -2, prevloss = -1;
   srand(time(NULL));
   for (i = 0; i < k; i++)
      ctr[i] = pts[rand() % n];
   while (fabs(curloss-prevloss) > TOL){
      d = distance (pts, n, ctr, k, clusters); 
      prevloss = curloss;
      curloss = d;
      update (ctr, k, pts, n, clusters);
   }
   return (clusters);
}

int main (int argc, char *argv[]){
   point data[NPTS]={
      {-1, -1},
      { 1, 1 },
      { 1, 2 },
      { 4, 5 },
      { 4, 7 },
      { 8, 9},
      {-5, -4},
      {-2, 3},
      {4, -6}
   };
   int i, *k;
   k = kmeans(data, NPTS, 3);
   for (i=0; i<NPTS; i++)
      printf("%f\t%f\t%d\n", data[i].x, data[i].y, k[i]);
   return (0);
}

