#include <stdio.h>
#include <string.h>
#define LEN_MAX 10

void swap (char *str, int i, int j){
   int tmp;
   tmp = str[i];
   str[i] = str[j];
   str[j] = tmp;
}

void reverse (char *str, int i, int j){
   if (i < j){
      swap (str, i, j);
      reverse (str, ++i, --j);
   }
}

void next_perm (char *str, int len){
   int i, k;
   for (i = len-2; i >= 0; i--)
      if (str[i] < str[i+1])
         break;
   if (i < 0)
      reverse(str, 0, len-1);
   else
      for (k = len-1; k > i; k--)
         if (str[k] > str[i]){
            swap (str, i, k);
            reverse (str, i+1, len-1);
            break;
         }
}

int main(int argc, char *argv[]){
   char str[LEN_MAX];
   int n;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   strncpy (str, argv[1], LEN_MAX);
   str [LEN_MAX-1] = '\0';

   for(int i = 0; i < LEN_MAX; i++)
      if (str[i] == '\0'){
         n = i;
         break;
      }

   next_perm (str, n);

   printf ("%s\n", str);
   return (0);
}
