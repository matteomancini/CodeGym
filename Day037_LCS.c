#include <stdio.h>
#include <stdlib.h>

char* lcs (char *x, char *y, int l){
   int i, j, k, **table = calloc (l + 1, sizeof(int *));
   char *s;
   for (i = 0; i <= l; i++)
      table[i] = calloc (l + 1, sizeof(int));
   for (i = 1; i <= l; i++)
      for (j = 1; j <= l; j++)
         if (x[i-1] == y[j-1])
            table[i][j] = table[i-1][j-1] + 1;
         else
            table[i][j] =
               table[i-1][j] > table[i][j-1] ?
               table[i-1][j] : table[i][j-1];
   s = malloc ((table[l][l]) * sizeof (char));
   k = table[l][l] - 1;
   for (i = l, j = l; i > 0 && j > 0; i--, j--)
      if (x[i-1] == y[j-1])
         s[k--] = x[i-1];
      else if (table[i-1][j] < table[i][j-1])
         i++;
      else
         j++;

   return (s);
}

int main(){
   char x[] = {"shortestuniquesubsequence"};
   char y[] = {"longestcommonsubsequences"};
   int len = 25;
   char *s = lcs (&x[0], &y[0], len);
   printf ("%s\n", s);
   return (0);
}

