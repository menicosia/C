#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

main() {
	int g ;
	struct sockaddr_in server ;
	struct hostent *hp ;
	char buf[256] ;

	g = socket(AF_INET, SOCK_STREAM, 0) ;
	server.sin_family = AF_INET ;
	server.sin_port = htons(13) ;
	hp = gethostbyname("localhost") ;
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length) ;
	if (0 > connect(g, (struct sockaddr *)&server, sizeof(server))) {
		perror("connect to daytime failed") ;
	}
	read(g, buf, sizeof(buf)) ;
	server.sin_port = htons(25) ;
	if (0 > connect(g, (struct sockaddr *)&server, sizeof(server))) {
		perror("connect to smtp failed") ;
	}
	sleep(360) ;
	close(g) ;
	return(0) ;
}
