#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int u;
   int v;
} edge;

void print_graph (edge *g, int e){
   int i;
   for (i = 0; i < e; i++)
      printf ("(%d, %d)\n", g[i].u, g[i].v);
}

void substitute (edge *g, int old, int new, int e){
   int i;
   for (i = 0; i < e; i++){
      if (g[i].u == old)
         g[i].u = new;
      if (g[i].v == old)
         g[i].v = new;
   }
}

int contract (edge *g, int i, int e){
   int j, k, m;
   m = g[i].u > g[i].v ? g[i].v : g[i].u;
   substitute (g, g[i].v, m, e);
   substitute (g, g[i].u, m, e);
   for (j = 0; j < e; j++)
      if (g[j].v == g[j].u){
         for (k = j; k < e - 1; k++)
            g[k] = g[k+1];
         j--;
         e--;
      }

   return (e);
}

int mincut (edge *g, int v, int e){
   int i;
   while (v > 2){
      print_graph (g, e);
      i = rand() % e;
      printf ("\nCutting (%d, %d)\n\n", g[i].u, g[i].v);
      e = contract (g, i, e);
      v--;
   }

   print_graph (g, e);
   return (e);
}

int main (int argc, char argv[]){
   int v = 4, e = 5, c;
   edge *graph = malloc (e * sizeof(edge));
   graph[0].u = 0;
   graph[0].v = 1;
   graph[1].u = 0;
   graph[1].v = 2;
   graph[2].u = 0;
   graph[2].v = 3;
   graph[3].u = 1; 
   graph[3].v = 3;
   graph[4].u = 2;
   graph[4].v = 3;
   srand (time(NULL));
   c = mincut (graph, v, e);
   printf ("Number of cuts: %d\n", c);
   return (0);
}

