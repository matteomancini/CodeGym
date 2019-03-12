#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

int find_char (char *c, char *i){
   while (c > i)
      if (*c == *i++)
         return (1);
   return (0);
}

void longest_useq (char *str, char **u, char **v){
   char *i = str, *j = str;
   *u = str;
   *v = str;
   while (*j != '\0'){
      if (find_char (j, i))
         i++;
      else
         j++;
      if (j - i > *v - *u){
         *u = i;
         *v = j;
      }
   }
}

int main (int argc, char *argv[]){
   char seq[MAX_LEN];
   char *start, *end;

   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else
      strncpy (seq, argv[1], MAX_LEN);

   longest_useq (seq, &start, &end);
   while (end > start)
      printf ("%c", *start++);
   printf ("\n");
   return (0);
}

