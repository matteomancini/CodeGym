#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define NPTS 9

typedef struct {
   double x;
   double y;
} point;

double pdist (point p1, point p2){
   return (sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2)));
}

void ins_sort (point *p, int s, int e, int coor){
   point k;
   int i, j;
   double *c, *ck;
   for (i = s + 1; i < e; i++){
      k = p[i];
      ck = coor ? &(k.x) : &(k.y);
      c = coor ? &(p[i-1].x) : &(p[i-1].y);
      for (j = i - 1; j >= s && *c > *ck; j--){
         p[j+1] = p[j];
         c = coor ? &(p[j-1].x) : &(p[j-1].y);
      }
      p[j+1] = k;
   }
}

double bforce (point *p, int start, int end){
   int i, j;
   double min = DBL_MAX;
   for (i = start; i < end - 1; i++)
      for (j = start + 1; j < end; j++)
         if (pdist(p[i], p[j]) < min)
            min = pdist(p[i], p[j]);
   return min;
}

double search (point *p, int start, int end){
   ins_sort (p, start, end, 1);
   if ((end-start) < 2)
      return (bforce(p, start, end));

   point *mp = calloc (end - start, sizeof(point));
   point q, p1, p2;
   int middle, i, j, nmp = 0;
   double d1, d2, d, dsq;

   middle = (start + end) / 2;
   q = p[middle];
   d1 = search (p, start, middle);
   d2 = search (p, middle, end);
   d = d1 > d2 ? d2 : d1;

   ins_sort (p, start, end, 0);
   for (i = start; i < end; i++){
      if (fabs(p[i].x - q.x) < d){
         mp[nmp] = p[i];
         nmp++;
      }
   }

   for (i = 0; i < nmp - 1; i++){
      p1 = mp[i];
      for (j = i + 1; j < nmp; j++){
         p2 = mp[j];
         if (fabs(p1.y - p2.y) < d){
            dsq = pdist (p1, p2);
            d = d > dsq ? dsq : d;
         }
         else
            break;
      }
   }

   return (d);
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
   double k;
   k = search (data, 0, NPTS);
   printf ("%f\n", k);
   return (0);
}

