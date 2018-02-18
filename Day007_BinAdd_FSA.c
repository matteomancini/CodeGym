#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 11

void fsa (char *a, char *b, char *c, int len){
   char *transitions = "0010100110010111";
   char *r, *s, *t, cb = 48;
   for (int i = 0; i < len-1; i++){
      r = a + i;
      s = b + i;
      t = c + i;
      *t = transitions[(cb-48)*8+(*r-48)*4+(*s-48)*2];
      cb = transitions[1+(cb-48)*8+(*r-48)*4+(*s-48)*2];
   }
   *(t+1) = cb;
}

void swap (char *a, char *b){
   char tmp = *a;
   *a = *b;
   *b = tmp;
}

void reverse (char *str, int start, int end){
   if (start < end){
      swap (str + start, str + end - 1);
      reverse (str, start + 1, end - 1);
   }
}

int zeropad (char *str, int len){
   int j = MAX_LEN - 1;
   for (int i = 0; i < len-1; i++)
      if (str[i] == 0){
         str[i] = 48;
         if (j > i)
            j = i;
      }
   return (j);
}

int main (int argc, char *argv[]){
   char a[MAX_LEN], b[MAX_LEN];
   char c[MAX_LEN+1] = "0";
   int sh;
   if (argc < 3){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      strncpy (a, argv[1], MAX_LEN);
      sh = zeropad (a, MAX_LEN);
      reverse (a, 0, sh);
      strncpy (b, argv[2], MAX_LEN);
      sh = zeropad (b, MAX_LEN);
      reverse(b, 0, sh);
   }
   fsa (a, b, c, MAX_LEN);
   zeropad (c, MAX_LEN + 1);
   reverse (c, 0, MAX_LEN);
   printf ("%s\n", c);
   return (0);
}

