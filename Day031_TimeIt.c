#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap (int *x, int *y){
   int t = *x;
   *x = *y;
   *y = t;
}

void ins_sort (int *d, int n){
   int i, j, k;
   for (i = 1; i < n; i++){
      k = d[i];
      for (j = i - 1; j >= 0 && d[j] > k; j--)
         d[j+1] = d[j];
      d[j+1] = k;
   }
}

void sel_sort (int *d, int n){
   int i, j, m;
   for (i = 0; i < n - 1; i++){
      m = i;
      for (j = i + 1; j < n; j++)
         if (d[j] < d[m])
            m = j;
      swap (&d[m], &d[i]);
   }
}

double* timeit (void (*fp)(int *, int), int range[], int n){
   clock_t start, end;
   int i, k, *d;
   double *t = malloc (n * sizeof(double));
   for (k = 0; k < n; k++){
      srand (time(NULL));
      d = malloc (range[k] * sizeof(int));
      for (i = 0; i < range[k]; i++)
         d[i] = rand();
      start = clock();
      (*fp)(d, range[k]);
      end = clock();
      t[k] = (double)(end - start) / CLOCKS_PER_SEC;
   }
   return (t);
}

int main (){
   int range[] = {100, 1000, 10000, 100000};
   int i, n = 4;
   double *t_ins, *t_sel;
   void (*sort)(int *, int);
   sort = &ins_sort;
   t_ins = timeit (sort, range, n);
   for (i = 0; i < n; i++)
      printf ("%d: %f\t", range[i], t_ins[i]);
   printf ("\n");
   sort = &sel_sort;
   t_sel = timeit (sort, range, n);
   for (i = 0; i < n; i++)
      printf ("%d: %f\t", range[i], t_sel[i]);
   printf ("\n");
   return (0);
}

