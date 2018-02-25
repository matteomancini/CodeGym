#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct node{
   char c;
   int f;
   struct node *left, *right;
};

struct node* add_node (char c, int f, struct node *l, struct node *r){
   struct node* newnode = malloc (sizeof(struct node*));
   newnode -> left = l;
   newnode -> right = r;
   newnode -> c = c;
   newnode -> f = f;
   return (newnode);
}

void heap_sort (struct node **h, int n){
   struct node *k;
   int j;
   for (int i = 1; i < n; i++){
      k = h[i];
      for (j = i - 1; j>=0 && (h[j]->f) > (k->f); j--){
         h[j+1] = h[j];
      }
      h[j+1] = k;
   }
}

struct node** init_heap (char string[], int f[], int n){
   struct node **h = (struct node** ) malloc (n*sizeof(struct node*));

   for (int i = 0; i < n; i++)
      h[i] = add_node (string[i], f[i], NULL, NULL);

   heap_sort (h, n);

   return (h);
}

struct node* huffman (struct node **h, int n){
   while (n > 1){
      h[0] = add_node ('\0', (h[0]->f) + (h[1]->f), h[0], h[1]);
      for (int i=1; i<n-1; i++)
         h[i] = h[i+1];
      heap_sort (h, --n);
   }
   return (h[0]);
}

void print_tree (struct node *t, int *code, int n){
   if (t->left){
      code[n] = 0;
      print_tree (t->left, code, n+1);
   }
   if (t->right){
      code[n] = 1;
      print_tree(t->right, code, n+1);
   }
   if (!(t->right) && !(t->left)){
      printf ("%c\t", t->c);
      for (int i = 0; i < n; i++)
         printf("%d", code[i]);
      printf("\n");
   }
}

int main (int argc, char *argv[]){
   char string[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
   int freq[] = {37, 18, 29, 13, 30, 17, 6};
   int len = 7, n = 0, code[MAX_SIZE];

   struct node **h = init_heap (string, freq, len);
   struct node *t = huffman (h,len);
   
   print_tree(t, code, n);
   return (0);
}

