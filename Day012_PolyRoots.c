#include <stdio.h>
#include <math.h>
#define MAX_ORDER 5
#define MAX_ITER 1000
#define TOL 0.01

float f (float x, float *par, int n){
   float value = 0;
   for (int i = 0; i < n; i++)
      value += par[i] * pow(x, n-1-i);
   return (value);
}

float muller (float x0, float x1, float x2, float *par, int n){
   float res;
   float y0, y1, y2, x02, x12, y02, y12, a, b, c, r1, r2;
   for (int i = 0; i < MAX_ITER; i++){
      y0 = f (x0, par, n);
      y1 = f (x1, par, n);
      y2 = f (x2, par, n);
      x02 = x0 - x2;
      x12 = x1 - x2;
      y02 = y0 - y2;
      y12 = y1 - y2;
      c = y2;
      b = (y12*pow(x02,2)-y02*pow(x12,2)) / (x02*x12*(x02-x12));
      a = (y02*x12-y12*x02) / (x02*x12*(x02-x12));
      r1= (-2*c) / (b+sqrt(pow(b,2)-4*a*c));
      r2 = (-2*c) / (b-sqrt(pow(b,2)-4*a*c));
      if (r1 >= r2)
         res = r1 + x2;
      else
         res = r2 + x2;
      if (fabs(res-x2) < TOL){
         printf ("Found a root!\n");
         return (res);
      }
      x0 = x1;
      x1 = x2;
      x2 = res;
   }
   printf ("Max number of iterations reached\n");
   return (res);
}

int main (int argc, char *argv[]){
   float c[4] = {1.0, 2.0, 10.0, -20.0};
   int o = 4;
   float res = muller (0, 1, 2, c, o);
   printf ("%f\n", res);
   return (0);
}
