#include <stdio.h>
#define NODES 10
#define EDGES 6

int find (int *d, int i){
   if (i != d[i])
      d[i] = find (d, d[i]);
   return (d[i]);
}

void union_f (int *d, int i, int j){
   int p, q;
   p = find (d, i);
   q = find (d, j);
   if (p != q)
      d[p] = q;
}

int main (){
   int d[NODES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
   int c[EDGES][2] = {{0, 1}, {1, 2}, {0, 9}, {5, 6}, {6, 4}, {5, 9}};
   int i;

   for (i = 0; i < EDGES; i++)
      union_f (d, c[i][0], c[i][1]);

   for (i = 0; i < NODES; i++)
      printf ("%d -> %d\n", i, find(d, i));

   return (0);
}
