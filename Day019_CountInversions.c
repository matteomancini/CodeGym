#include <stdio.h>
#include <stdlib.h>

int merge (int *array, int *aux, int start, int middle, int end){
   int i = start, j = middle, inversions = 0;
   for (int k = start; k < end; k++){
      if (i < middle && j < end){
         if (array[i] < array[j])
            aux[k]=array[i++];
         else{
            aux[k]=array[j++];
            inversions += middle - i;
         }
      }
      else if (i < middle)
         aux[k] = array[i++];
      else if (j < end)
         aux[k] = array[j++];
   }

   for (i = start; i < end; i++)
      array[i] = aux[i];

   return (inversions);
}

int mergesort (int *array, int *aux, int start, int end){
   int middle, inversions = 0;
   if ((end-1) > start){
      middle = (end + start) / 2;
      inversions = mergesort(array, aux, start, middle);
      inversions += mergesort(array, aux, middle, end);
      inversions += merge(array, aux, start, middle, end);
   }
   return (inversions);
}

int main (int argc, char *argv[]){
   int inv = 0, n;
   int *array, *aux;
   char *endptr;
   if (argc < 3){
      printf("Not enough arguments\n");
      return (1);
   }
   else{
      n = argc - 1;
      array = malloc (n*sizeof(int));
      aux = malloc (n*sizeof(int));
      for (int a = 1; a < n + 1; a++){
         array[a-1] = strtol (argv[a], &endptr, 10);
         if (! argv[a] || *endptr)
            return(1);
      }
   }
   inv = mergesort (array, aux, 0, n);
   printf("Number of inversions: %d\n", inv);
   return (0);
}

