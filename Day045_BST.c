#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ITER 1000
#define SAMP 8

struct node{
   int x;
   struct node *left;
   struct node *right;
};

void add (struct node **tree, int v){
   if (*tree == NULL){
      *tree = malloc (sizeof(struct node));
      (*tree)->x = v;
   }
   else
      if (v > (*tree)->x)
         add (&((*tree)->right), v);
      else if (v < (*tree)->x)
         add (&((*tree)->left), v);
}

void iterate (struct node *tree){
   if (tree != NULL){
      printf ("%d\n", tree->x);
      iterate (tree->left);
      iterate (tree->right);
   }
}

struct node *search (struct node *tree, int v){
   if (tree == NULL)
      return tree;
   else if (v > tree->x)
      search (tree->right, v);
   else if (v < tree->x)
      search (tree->left, v);
   else
      return tree;
}

int depth (struct node *tree){
   int r, l;
   if (tree == NULL)
      return (0);
   else{
      l = depth (tree->right);
      r = depth (tree->left);
      if (l > r)
         return (l + 1);
      else
         return (r + 1);
   }
}

int smp_index (int *smp, int i){
   int s;
   for (s = 0; s < SAMP; s++)
      if (i + 1 == smp[s])
         return (s);
   return (-1);
}

int main (){
   struct node *bst;
   int i, j, p, smp[SAMP] = {10, 20, 50, 100, 200, 500, 1000, 2000};
   double points[SAMP] = {0.0};

   srand (time(0));
   for (i = 0; i < ITER; i++){
      bst = NULL;
      for (j = 0; j < 3 * ITER; j++){
         add (&bst, rand() % RAND_MAX);
         p = smp_index (smp, j);
         if (p >= 0)
            points[p] += depth(bst);
      }
   }

   for (p = 0; p < SAMP; p++){
      points[p] /= 1000;
      printf ("%.3f\t", points[p]);
   }
   printf("\n");
   return (0);
}
