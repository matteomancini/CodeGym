#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 20

typedef struct {
   int size;
   double stack[MAX_SIZE];
} stream;

void stream_init (stream *s){
   s->size = 0;
}

void stream_put (stream *s, double d){
   s->stack[s->size++] = d;
}

double stream_get (stream *s){
   double d = 0;
   if ((s->size) > 0)
      d = s->stack[--(s->size)];
   return d;
}

double postfix (char **expression, int n){
   stream *vals = calloc (1, sizeof(stream));
   stream_init (vals);
   char *str, *ptr;
   double a, b, x;
   for(int i = 0; i < n; i++){
      str = expression[i];
      x = strtod (str, &ptr);
      if(! str || *ptr){
         a = stream_get (vals);
         b = stream_get (vals);
         switch (*str){
            case 'a':
               x = a + b;
               break;
            case 's':
               x = b - a;
               break;
            case 'm':
               x = a * b;
               break;
            case 'd':
               x = b / a;
               break;
            case 'p':
               x = pow (a, b);
            default:
               x = 0;
         }
      }
      stream_put (vals, x);
   }
   return (stream_get(vals));
}

int main (int argc, char *argv[]){
   char **ops;
   int n;
   double res;
   if (argc < 4){
      printf ("Not enough arguments\n");
      return (1);
   }
   else if (argc > MAX_SIZE+1){
      printf ("Too many arguments\n");
      return (1);
   }
   else{
      n = argc - 1;
      for (int i = 1; i < n+1; i++){
         ops[i-1] = argv[i];
      }
   }
   res = postfix (ops, n);
   printf ("%f\n", res);
   return (0);
}

