#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 50

void otp (char **str, char *key, int n, int w){
   for (int i = 0; i < w; i++)
      for (int j = 0; j < n; j++)
         str[i][j] = str[i][j] ^ key[j];
}

int strip (char *str, int n){
   int i;
   for (i = 0; i < n; i++)
      if (str[i] == '\0')
         break;
   return (i+1);
}

char** crack (char **str, int n, int w){
   char **cracked = (char **) calloc (w, sizeof(char*));
   int i, j, k, count;
   char key = 0, key_o = 0, c[]="abcdefghijklmnopqrstuvxwz";
   int len = sizeof(c) / sizeof(char);
   for (j = 0; j < w; j++)
      cracked[j] = (char *) calloc (n, sizeof(char));
   for (i = 0; i < n; i++){
      count=0;
      for (k = 0; k < len-1; k++){
         for (j = 0; j < w; j++){
            if (((c[k] ^ str[j][i]) < 97) || ((c[k] ^ str[j][i]) > 122)){
               key = key_o;
               break;
            }
            key = c[k];
         }
         if (key_o != key)
            count++;
         key_o = key;
      }
      for (j = 0; j < w; j++)
         cracked[j][i] = (count == 1 ? key ^ str[j][i] : '*');
   }
   return (cracked);
}

int main (int argc, char *argv[]){
   char **str, key[MAX_LEN];
   char **crk;
   int n, w, i;
   if (argc < 4){
      printf ("Not enough arguments\n");
      return (1);
   }
   else{
      w = argc - 2;
      str = (char **) calloc (w, sizeof(char*));
      strncpy (key, argv[1], MAX_LEN);
      n = strip(key, MAX_LEN);
      for (i = 2; i < w+2; i++){
         str[i-2] = (char *) calloc (n, sizeof(char));
         strncpy (str[i-2], argv[i], n+1);
      }
   }
   otp (str, key, n, w);
   for (i = 0; i < w; i++)
      printf ("Crypted: %s\n", str[i]);
   crk = crack (str, n, w);
   otp (str, key, n, w);
   for (i = 0; i < w; i++){
      printf ("Decrypted: %s\n", str[i]);
      printf ("Cracked: %s\n", crk[i]);
   }
   return (0);
}

