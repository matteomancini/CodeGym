#include <stdio.h>
#include <stdlib.h>

typedef struct{
   double x, y;
} point;

double cross (point u, point v){
   return (u.x * v.y - u.y * v.x);
}

point sub (point u, point v){
   point p;
   p.x = u.x - v.x;
   p.y = u.y - v.y;
   return (p);
}

int split (point *p, point *spl, int n, point u, point v){
   int i, k = 0;
   for (i = 0; i < n; i++)
      if (cross (sub(p[i], u), sub(v, u)) < 0)
         spl[k++] = p[i];
   return (k);
}

void extend (point *p, int n, point *aux, int *k, point u, point v){
   if (n > 0){
      point *p1, *p2, w;
      int i, c, min, pp1, pp2;
      w = p[0];
      min = cross (sub(p[0],u), sub(v,u));
      for (i = 1; i < n; i++){
         c = cross (sub(p[i],u), sub(v,u));
         if (c < min){
            min = c;
            w = p[i];
         }
      }
      p1 = calloc (n, sizeof(point));
      p2 = calloc (n, sizeof(point));
      pp1 = split (p, p1, n, w, v);
      pp2 = split (p, p2, n, u, w);
      extend (p1, pp1, aux, k, w, v);
      extend (p2, pp2, aux, k, u, w);
      aux[(*k)++] = w;
   }
}

int convex_hull (point *p, int n, point *aux){
   int i, l, r, k;
   double min, max;
   point u, v, *left, *right;
   min = p[0].x;
   max = p[0].x;
   for (i = 1; i < n; i++){
      if (p[i].x < min){
         min = p[i].x;
         u = p[i];
      }
      if (p[i].x > max){
         max = p[i].x;
         v = p[i];
      }
   }
   left = calloc (n, sizeof(point));
   right = calloc (n, sizeof(point));
   l = split (p, left, n, u, v);
   r = split (p, right, n, v, u);
   aux[0] = v;
   aux[1] = u;
   k = 2;
   extend (left, l, aux, &k, u, v);
   extend (right, r, aux, &k, v, u);
   return (k);
}

int main(){
   int n = 10, k, i;
   point *p = calloc (n, sizeof(point));
   p[0].x = 3;
   p[0].y = 2;
   p[1].x = 10;
   p[1].y = 30;
   p[2].x = -5;
   p[2].y = -4;
   p[3].x = -3;
   p[3].y = 1;
   p[4].x = 3;
   p[4].y = -2;
   p[5].x = 43;
   p[5].y = 26;
   p[6].x = -13;
   p[6].y = -12;
   p[7].x = -10;
   p[7].y = -12;
   p[8].x = -32;
   p[8].y = -4;
   p[9].x = -10;
   p[9].y = 25;

   point *h = calloc (n, sizeof(point));
   k = convex_hull (p, n, h);
   for (i = 0; i < k; i++)
      printf ("[%f, %f], ", h[i].x, h[i].y);
   printf ("\n");
   return (0);
}

