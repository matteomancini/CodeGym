#include <stdio.h>
#include <math.h>

double gradient (double x, double (*f)(double), double delta){
   return (((*f)(x+delta) - (*f)(x-delta))/(2*delta));
}

int main (){
   double delta = 0.0001;
   double x = 1.5;
   double (*f)(double) = &sin;
   printf ("x0 = %f\n", x);
   printf ("(sin(x0))' = %f\n", gradient (x, f, delta));
   f = &cos;
   printf ("(cos(x0))' = %f\n", gradient (x, f, delta));
   f = &sqrt;
   printf ("(sqrt(x0))' = %f\n", gradient (x, f, delta));
   return (0);
}

