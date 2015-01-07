#include <stdlib.h>
#include <stdio.h>
int main() {
  int i=7;
  FILE *g;
  g = fopen("foo", "w") ;
  fwrite(&i, sizeof(i), 1, g);
  fclose(g) ;
  exit(0) ;
}
