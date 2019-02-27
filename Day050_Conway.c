#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init (int ***grid, int n){
   int i, j;
   for (i = 1;  i < n - 1; i++)
      for (j = 1; j < n - 1; j++)
         (*grid)[i][j] = rand() % 2;
}

int neighbours (int **grid, int r, int c){
   int i, j, s = 0;
   for (i = r - 1; i <= r + 1; i++)
      for (j = c - 1; j <= c + 1; j++)
         s += grid[i][j];
   return (s - grid[r][c]);
}

void update (int ***grid, int n){
   int i, j, **nn = calloc (n, sizeof(int *));
   for (i = 0; i < n; i++)
      nn[i] = calloc (n, sizeof(int));

   for (i = 1; i < n - 1; i++)
      for (j = 1; j < n - 1; j++)
         nn[i][j] = neighbours ((*grid), i, j);

   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         (*grid)[i][j] = nn[i][j]==3 ||
            (nn[i][j] == 2 && (*grid)[i][j] == 1);
}

void printgrid (int **grid, int n){
   int i, j;
   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++)
         if (grid[i][j] == 1)
            printf ("* ");
         else
            printf ("o ");
      printf ("\n");
   }
   printf ("\n");
}

int main (int argc, char *argv[]){
   int **grid;
   int i, n = 10, its = 10;
   char *endptr;
   if (argc > 1){
      if (*argv[1] || *endptr)
         n = strtol (argv[1], &endptr, 10);
      if (argc > 2)
         if (*argv[2] || *endptr)
            its = strtol (argv[2], &endptr, 10);
   }
   grid = calloc (n, sizeof(int *));
   for (i = 0; i < n; i++)
      grid[i] = calloc (n, sizeof(int));
   srand (time(0));
   init (&grid, n);
   printgrid (grid, n);
   for (i = 1; i <= its; i++){
      update (&grid, n);
      printgrid (grid, n);
   }
   return (0);
}
