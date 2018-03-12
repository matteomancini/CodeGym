#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIM 100

struct list{
   char c;
   int i;
   struct list *next;
};

struct list* lookup (struct list *t, char s){
   struct list *c = t;
   while (c != NULL){
      if (c->c == s)
         return c;
      c = c->next;
   }
   return (NULL);
}

int checktab (struct list *t, char s, int l){
   struct list *r = lookup (t, s);
      
   return (r==NULL ? l : r->i);
}

struct list* init_table (char *s, int l){
   struct list *c, *r, *t;
   int i;
   for (i = 0; i < l; i++){
      r = NULL;
      r = lookup (t, s[i]);
      if (r != NULL)
         r->i = l - i;
      else{
         if (t == NULL){
            t = calloc (1, sizeof(struct list));
            c = t;
         }
         else{
            c->next = calloc (1, sizeof(struct list));
            c = c->next;
         }
         c->c = s[i];
         c->i = l - i;
      }
   }
   return t;
}

void search (char *text, int n, char *pattern, int k){
   struct list *t;
   char *c;
   int i, j = k;
   t = init_table (pattern, k);
   for (i = 0; i + k < n; i += j){
      printf ("Search @ %d", i);
      c = &text[i];
      if (!strncmp (c, pattern, k))
         printf (" - Found it!");
      j = checktab (t, text[i+k], k+1);
      printf ("\n");
   }
}

int len (char *s, int dim){
   int i;
   for (i = 0; i < dim; i++)
      if (s[i] == '\0')
         return i;
   return dim;
}

int main(int argc, char *argv[]){
   char text[MAX_DIM], pattern[MAX_DIM];
   int n, k;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      strncpy (text, argv[1], MAX_DIM);
      strncpy (pattern, argv[2], MAX_DIM);
   }
   n = len (text, MAX_DIM);
   k = len (pattern, MAX_DIM);
   search (text, n, pattern, k);
   return (0);
}

