#include <stdio.h>
#include <stdlib.h>
#define NW 3
#define NS 5

int perceptron (int *x, int *w, int n){
   int y = 0;
   for (int i = 0; i < n; i++)
      y += x[i] * w[i];
   return (y>=0);
}

double train (int x[NS][NW], int s, int n, int *y, int *w){
   int k, h = 0;
   double acc = 0;
   for (k = 0; k < s; k++){
      h = perceptron (x[k], w, n);
      if (h != y[k])
         for (int i = 0; i < n; i++)
            if (y[k] == 1)
               w[i] += x[k][i];
            else
               w[i] -= x[k][i];
   }
   for (k = 0; k < s; k++)
      acc += (perceptron(x[k], w, n) == y[k]);
   return (acc/s);
}

void printw (int *w, int n){
   for (int i = 0; i < n; i++)
      printf("%d ", w[i]);
}

int main(int argc, char *argv[]){
   int n = NW, s = NS;
   int x[NS][NW] = { {0,1,1}, {1,0,1}, {1,1,1}, {-1,1,1}, {1,-1,1} };
   int y[] = {1, 1, 1, 0, 0};
   int *w = calloc (n, sizeof(int));
   double a;
   for (int t = 0; t < 5; t++){
      printf ("%d: ", t);
      a = train (x, s, n, y, w);
      printw (w, n);
      printf ("\t%f\n", a);
   }
   return (0);
}
