#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

main(int argc, char **argv) {
   int fd;

   if (argc < 2) { printf("ERR: must provide filename.\n"); exit(1); }
   fd = open(argv[1], O_CREAT|O_TRUNC, 0644);
   if (-1 == fd) { perror("Opening file") ; exit(-1); }
   close(fd);
   exit(0);
}
