#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* rotate (char *s, int k){
   int i;
   char *r = malloc (k * sizeof(char));
   for (i = 0; i < k - 1; i++)
      r[i] = s[i+1];
   r[k-1] = s[0];
   return (r);
}

int strcmp_wrap (const void *a, const void *b){
   return (strcmp (*(char **) a, *(char **) b));
}

int bwt (char *txt, int len, char **bwt){
   int i, k = -1;
   char **rt = malloc (len * sizeof(char *));
   rt[0] = malloc (len * sizeof(char));
   strcpy (rt[0], txt);
   for (i = 1; i < len; i++)
      rt[i] = rotate (rt[i-1], len);
   qsort (rt, len, sizeof(char *), strcmp_wrap);
   *bwt = malloc (len * sizeof(char));
   for (i = 0; i < len; i++){
      (*bwt)[i] = rt[i][len-1];
      if (! strcmp(rt[i], txt))
         k = i;
   }
   return (k);
}

char* ibwt (char *bwt, int len, int k){
   int i, j, h;
   char **rt = malloc (len * sizeof(char *));
   for (i = 0; i < len; i++)
      rt[i] = malloc (len * sizeof(char));
   for (i = 0; i < len; i++){
      for (h = i; h > 0; h--)
         for (j = 0; j < len; j++)
            rt[j][h] = rt[j][h-1];
      for (j = 0; j < len; j++)
         rt[j][0] = bwt[j];
      qsort (rt, len, sizeof(char *), strcmp_wrap);
   }

   return (rt[k]);
}

int main(int argc, char *argv[]){
   char *txt, *bw, *ibw;
   int len, k;
   if (argc < 2){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      txt = argv[1];
      len = strlen (txt);
   }
   k = bwt (txt, len, &bw);
   ibw = ibwt (bw, len, k);
   printf ("%s, %d -> %s\n", bw, k, ibw);
   return (0);
}

