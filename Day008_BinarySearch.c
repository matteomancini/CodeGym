#include <stdio.h>
#include <stdlib.h>
#define LEN_MAX 20

int bin_search (int *data, int len, int item){
   int left = 0;
   int right = len - 1;
   int mid;
   while (right >= left){
      mid = (left+right) / 2;
      if (item > data[mid])
         left = mid + 1;
      else if (item < data[mid])
         right = mid - 1;
      else
         return mid;
   }
   return (-1);
}

int main(int argc, char *argv[]){
   int *data, item, n, res;
   char *endptr;
   if (argc < 4){
      printf ("Not enough arguments\n");
      return (1);
   }
   else if (argc > LEN_MAX+2){
      printf ("Too many arguments\n");
      return (1);
   }
   else{
      n = argc - 2;
      data = malloc (n*sizeof(int));
      for (int i=0; i<n+1; i++){
         if (i < n)
            data[i] = strtol(argv[i+1], &endptr, 10);
         else
            item = strtol(argv[i+1], &endptr, 10);
         if (! argv[i+1] || *endptr){
            printf ("Invalid number: %c\n", argv[i+1]);
            return (1);
         }
      }
   }
   res = bin_search (data, n, item);
   printf ("%d\n", res);
   return (0);
}
