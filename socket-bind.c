#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

main() {
	int g ;
	struct sockaddr_in server ;

	g = socket(AF_INET, SOCK_STREAM, 0) ;
	server.sin_family = AF_INET ;
	server.sin_addr.s_addr = INADDR_ANY ;
	server.sin_port = htons(8202) ;
	if (bind(g, (struct sockaddr *)&server, sizeof(server))) {
		perror("bind") ;
		exit(1) ;
	}
	sleep(360) ;
	return(0) ;
}


