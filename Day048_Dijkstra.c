#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define NODES 5

int mindistance (int *d, int v[], int n){
   int min = INT_MAX, i, m;
   for (i = 0; i < n; i++)
      if (!v[i] && d[i] < min){
         min = d[i];
         m = i;
      }
   return (m);
}

int *dijkstra (int adj[][NODES], int start){
   if (start >= NODES)
      return (NULL);

   int i, j, m, *d = calloc (NODES, sizeof(int));
   int v[NODES] = {0};

   for (i = 0; i < NODES; i++)
      if (i != start)
         d[i] = INT_MAX;

   for (i = 0; i < NODES - 1; i++){
      m = mindistance (d, v, NODES);
      v[m] = 1;
      for (j = 0; j < NODES; j++)
         if (!v[j] && adj[m][j] && d[m] + adj[m][j] < d[j])
            d[j] = d[m] + adj[m][j];
   }

   return (d);
}

int main (){
   int a[NODES][NODES] =
      {{0, 10, 0, 30, 100},
      {10, 0, 50, 0, 0},
      {0, 50, 0, 20, 10},
      {30, 0, 20, 0, 60},
      {100, 0, 10, 60, 0}};
   int i, x, *d;
   srand (time(0));
   x = rand () % 5;
   d = dijkstra (a, x);
   for (i = 0; i < NODES; i++)
      if (i != x)
         printf ("%d -> %d: %d\n", x, i, d[i]);
   return (0);
}
