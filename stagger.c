#include <stdio.h>

/* Little proggy to take a line of input and print them one character
 * at a time; looks interesting (over a modem).
 */

#define MAX_LEN 80
main (int argc, char **argv) {
  int i, x, l ;
  FILE *f ;
  char ch ;
  char *str, *tmp ;

  if (2 != argc) {
    fprintf(stderr, "Usage: %s output-file\n", argv[0]) ;
    exit(1) ;
  }

  if (NULL == (f = fopen(argv[1], "w"))) {
    fprintf(stderr, "%s: Unable to open file: %s\n", argv[0], argv[1]) ;
    exit(1) ;
  }

  str = (char *) malloc(sizeof(char) * MAX_LEN) ;

  while (NULL != fgets(str, MAX_LEN, stdin)) {
    l = strlen(str) ;
    tmp = (char *) calloc(1, sizeof(char) * (l + 1)) ;

    for (x = 0 ; x != l ; x++) {
      tmp[x] = str[x] ; 
      tmp[x+1] = '\0' ;
      for (i = 0 ; i <= 5 ; i++) {
		fprintf(f, "%s\r", tmp) ;
      }
    }
  }
  fputc('\n', f) ;
  fclose(f) ;
}

