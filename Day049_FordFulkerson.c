#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODES 8

typedef struct {
   int d[NODES];
   int size;
} queue;

void queue_init (queue *q){
   q->size = 0;
}

void queue_push (queue *q, int x){
   if (q->size < NODES)
      q->d[(q->size)++] = x;
}

int queue_pop (queue *q){
   int i, f = -1;
   if (q->size > 0){
      f = q->d[0];
      for (i = 0; i < (q->size) - 1; i++)
         q->d[i] = q->d[i+1];
      q->d[--(q->size)] = 0;
   }
   return (f);
}

int queue_size (queue *q){
   return (q->size);
}

int bfs (int res[NODES][NODES], int src, int snk, int p[]){
   int x, i, v[NODES] = {0};
   queue q;
   queue_init (&q);
   queue_push (&q, src);
   v[src] = 1;
   p[src] = -1;

   while (queue_size (&q) > 0){
      x = queue_pop (&q);
      for (i = 0; i < NODES; i++)
         if (v[i] == 0 && res[x][i] > 0){
            queue_push (&q, i);
            p[i] = x;
            v[i] = 1;
         }
   }
   return (v[snk]);
}

int fordfulkerson (int g[NODES][NODES], int src, int snk){
   int m, f, i, j, res[NODES][NODES], pth[NODES];
   m = 0;
   for (i = 0; i < NODES; i++)
      for (j = 0; j < NODES; j++)
         res[i][j] = g[i][j];
   while (bfs (res, src, snk, pth)){
      f = INT_MAX;
      for (i = snk; i != src; i = pth[i]){
         j = pth[i];
         f = f > res[j][i] ? res[j][i] : f;
      }
      for (i = snk; i != src; i = pth[i]){
         j = pth[i];
         res[j][i] -= f;
         res[i][j] += f;
      }
      m += f;
   }
   return (m);
}

int main (){
   int m, g[NODES][NODES] = {
      {0, 4, 5, 7, 0, 0, 0, 0},
      {0, 0, 0, 0, 7, 0, 0, 0},
      {0, 0, 0, 0, 6, 4, 1, 0},
      {0, 0, 0, 0, 0, 8, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 7},
      {0, 0, 0, 0, 0, 0, 0, 6},
      {0, 0, 0, 0, 0, 0, 0, 4},
      {0, 0, 0, 0, 0, 0, 0, 0}};
   m = fordfulkerson (g, 0, 7);
   printf ("Max flow: %d\n", m);
   return (0);
}
