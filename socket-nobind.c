#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

main() {
	int g ;

	g = socket(AF_INET, SOCK_STREAM, 0) ;
	sleep(360) ;
	return(0) ;
}


