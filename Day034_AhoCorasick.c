#include <stdio.h>
#include <stdlib.h>
#define MAX_S 500
#define MAX_C 26

int o[MAX_S];
int f[MAX_S];
int g[MAX_S][MAX_C];

typedef struct {
   int size;
   int data[MAX_S];
} queue;

void q_init (queue *q){
   q->size = 0;
}

void q_push (queue *q, int n){
   if (q->size < MAX_S)
      q->data[(q->size)++] = n;
}

int q_pop (queue *q){
   int n = -1, i;
   if (q->size > 0){
      n = q->data[0];
      for (i = 0; i < (q->size) - 1; i++)
         q->data[i] = q->data[i+1];
      q->data[--(q->size)] = 0;
   }
   return (n);
}

int state_machine (char **words, int *k, int n){
   int i, j;
   queue q;
   for (i = 0; i < MAX_S; i++){
      f[i] = -1;
      o[i] = 0;
      for (j = 0; j < MAX_C; j++)
         g[i][j] = -1;
   }
   int s = 1, cs, ind;

   for (i = 0; i < n; i++){
      cs = 0;
      for (j = 0; j < k[i]; j++){
         ind = words[i][j] - 'a';
         if (g[cs][ind] == -1)
            g[cs][ind] = s++;
         cs = g[cs][ind];
      }
      o[cs] |= (1 << i);
   }

   for (i = 0; i < MAX_C; i++)
      if (g[0][i] == -1)
         g[0][i] = 0;

   q_init (&q);
   for (i = 0; i < MAX_C; i++)
      if (g[0][i] != 0){
         f[g[0][i]] = 0;
         q_push (&q, g[0][i]);
      }

   while (q.size > 0){
      cs = q_pop (&q);
      for (i = 0; i < MAX_C; i++)
         if (g[cs][i] != -1){
            ind = f[cs];
            while (g[ind][i] == -1)
               ind = f[ind];
            ind = g[ind][i];
            f[g[cs][i]] = ind;
            o[g[cs][i]] |= o[ind];
            q_push (&q, g[cs][i]);
         }
   }

   return (s);
}

int next_state (int s, char c){
   int a = s;
   int i = c - 'a';

   while (g[a][i] == -1)
      a = f[a];

   return (g[a][i]);
}

void search (char *txt, int len, char **words, int *k, int n){
   int i, j, s = 0;
   state_machine (words, k, n);
   for (i = 0; i < len; i++){
      s = next_state (s, txt[i]);
      if (o[s] != 0)
         for (j = 0; j < n; j++)
            if (o[s] & (1 << j))
               printf("%s: %d -> %d\n", words[j], i - k[j] + 1, i);
   }
}

int main (int argc, char *argv[]){
   char **words;
   int wrd = 4;
   words = malloc (wrd * sizeof(char *));
   words[0] = "bar";
   words[1] = "ara";
   words[2] = "bara";
   words[3] = "barbara";
   int len[4] = {3, 3, 4, 7};
   char text[] = "barbarianbarbarasaidbarabum";
   int t = 27;
   search (&text[0], t, words, &len[0], 4);
   return (0);
}

