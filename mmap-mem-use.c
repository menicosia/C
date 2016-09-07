/* A brief program to demo the difference between RSS and SZ when a program mmap()s large files.
   Run this. Then run:
     ps -elF | awk -e 'NR == 1 {print}' -e '/mem-use/ && ! /grep/ {print}'
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

main (int argc, char *argv[]) {
  int FD ;
  char *memspan ;
  size_t length ;
  ssize_t s ;
  long pgsize ;
  float kbytes ;

  pgsize = sysconf(_SC_PAGESIZE) ;
  printf("Page size is: %d\n", pgsize) ;

  if (argc > 1) {
    length = atoi(argv[1]) * pgsize ;
  } else {
    length = 128 * pgsize ;
  }
  kbytes = length/1024 ;
  printf("Planning to allocate %2.0fKB\n", kbytes) ;

  FD = open("bigfile", O_RDWR) ;
  if (-1 == FD) {
    perror("open failed") ;
    exit(-1) ;
  }

  memspan = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, FD, 0) ;
  if (MAP_FAILED == memspan) {
    perror("map failed") ;
    exit(-1) ;
  }

  printf("sleeping...\n") ;
  sleep(90) ;
}
