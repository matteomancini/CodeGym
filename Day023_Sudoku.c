#include <stdio.h>
#include <stdlib.h>

void print_grid (int *grid){
   int i, j;
   for (i = 0; i < 9; i++){
      for (j = 0; j < 9; j ++)
         printf("%d ", grid[j+i*9]);
      printf("\n");
   }
}

int sudoku (int *grid, int n){
   if (n >= 81)
      return (1);

   if (grid[n] != 0)
      return (sudoku(grid, n+1));

   int i = n / 9;
   int j = n % 9;

   int v, av, k, l;
   int *x = calloc (9, sizeof(int));
   for (v = 0; v < 9; v++){
      for (av = 0; av < 9; av++)
         if (grid[av+i*9] == v+1 ||
               grid[j+av*9] == v+1)
            x[v] = 1;
      if (x[v] == 0)
         for (k = 0; k < 3; k++)
            for (l = 0; l < 3; l++)
               if (grid[l+(j/3)*3+(i/3)*27+k*9] == v+1)
                  x[v] = 1;
   }
      
   for (v = 0; v < 9; v++){
      if (x[v] == 0){
         grid[n] = v + 1;
         if (sudoku (grid, n+1) != 0)
            return (1);
         grid[n] = 0;
      }
   }

   return (0);
}

int main (int argc, char *argv[]){
   int hard[81] = { 8, 0, 0, 1, 0, 9, 0, 7, 0,
      0, 9, 0, 0, 0, 0, 8, 0, 0,
      5, 0, 3, 0, 4, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 7, 9, 0,
      0, 0, 7, 2, 6, 5, 3, 0, 0,
      0, 3, 8, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 9, 0, 4, 0, 1,
      0, 0, 6, 0, 0, 0, 0, 2, 0,
      0, 5, 0, 4, 0, 2, 0, 0, 3};
   int out;
   out = sudoku (hard, 0);
   if (out)
      print_grid (hard);
   else
      printf("Ops! No solution found!\n");
   return (0);
}

