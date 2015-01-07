#include <stdio.h>
#include <stdlib.h>

struct chunk {
    struct chunk *next ;
    char *chunky ;
} ;
#define CHUNK_NULL (struct chunk *)0

int newchunk(struct chunk **chunkl) ;

int newchunk(struct chunk **chunkl) {
    struct chunk *newchunk ;

    if (NULL == (newchunk = malloc(sizeof(struct chunk)))) {
        return(0) ;
    }
    if (NULL == (newchunk->chunky = calloc(1024, sizeof(char)))) {
        return(0) ;
    }
    newchunk->next = *chunkl ;
    *chunkl = newchunk ;
    return(1) ;
}
   
main(int argc, char **argv) {
    int i, max ;
    struct chunk *chunkl ;
    char *maxChunks = argv[1] ;

    max = atoi(maxChunks) ;
    printf("Collecting %d chunks...\n", max) ;

    for (i = 0 ; i <= max ; i++) {
        if (!newchunk(&chunkl)) {
            printf("Denied at chunk %d. Exiting.\n", i) ;
            exit(1) ;
        }
        else if (0 == i % 10) {
            printf("Collected %d chunks...\n", i) ;
        }
    }
    printf("Max, %d, reached. Exiting normally.\n", max) ;
}
