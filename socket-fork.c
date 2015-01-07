#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int getLine(FILE *LOG, char id, int srv_sock) ;

int main() {
	int srv_sock, one=1 ;
    FILE *LOG ;
    pid_t ppid, kpid ;
	struct sockaddr_in srv ;

    LOG = fopen("./sf.log", "a+") ;
    setlinebuf(LOG) ;
	srv_sock = socket(AF_INET, SOCK_STREAM, 0) ;
    setsockopt(srv_sock, SOL_SOCKET, SO_REUSEADDR, &one, one) ;
	srv.sin_family = AF_INET ;
	srv.sin_addr.s_addr = INADDR_ANY ;
	srv.sin_port = htons(8202) ;
	if (bind(srv_sock, (struct sockaddr *)&srv, sizeof(srv))) {
		perror("bind") ;
		exit(1) ;
	}
	listen(srv_sock, 5);
    if (fork()) {
        /* Parent process */
        ppid = getpid() ;
        fprintf(LOG, "[P] PPID: %d (sudo lsof -p %d)\n", ppid, ppid) ;
        fprintf(LOG, "[P] Socket is listening. Send a line.\n") ;
        getLine(LOG, 'P', srv_sock) ;
        fprintf(LOG, "[P] Sleeping 1 minute...\n") ;
        sleep(60) ;
        fprintf(LOG, "[P] Closing listening socket.\n") ;
        close(srv_sock) ;
        fprintf(LOG, "[P] Sleeping 2 minutes...\n") ;
        sleep(120) ;
        fprintf(LOG, "[P] Parent exiting.\n") ;
        fclose(LOG) ;
        exit(0) ;
    } else {
        /* Child process */
        fclose(stdin) ;
        fclose(stdout) ;
        fclose(stderr) ;
        if (fork()) {
            exit(0) ;
        } else {
            kpid = getpid() ;
            fprintf(LOG, "[C] CHILD PID: %d (sudo lsof -p %d)\n", kpid, kpid);
            fprintf(LOG, "[C] Sleeping 1 minute...\n") ;
            sleep(60) ;
            fprintf(LOG, "[C] Child socket is listening. Send a line.\n") ;
            getLine(LOG, 'C', srv_sock) ;
            fprintf(LOG, "[C] OK, base tests complete.\n") ;
            fprintf(LOG, "[C] Sleeping 1 minute for parent close & exit...\n");
            sleep(60) ;
            fprintf(LOG, "[C] Child socket is listening? Send a line.\n") ;
            getLine(LOG, 'C', srv_sock) ;
            fprintf(LOG, "[C] Child exiting.\n") ;
            close(srv_sock) ;
            exit(0) ;
        }
    }
    /* NOTREACHED */
    exit(1) ;
}

int getLine(FILE *LOG, char id, int srv_sock) {
    int cl_sock, nbytes, addrlen ;
    char rbuf[1024] ;
    struct sockaddr_in cl ;
    struct hostent *cl_name ;

    addrlen = sizeof(cl) ;
    cl_sock = accept(srv_sock, (struct sockaddr *)&cl, &addrlen) ;
    cl_name = gethostbyaddr((char *)&cl.sin_addr, sizeof(cl.sin_addr),
                            cl.sin_family) ;
    fprintf(LOG, "[%c] Connection from: %s:%d\n", id,
            cl_name->h_name, cl.sin_port) ;
    nbytes = read(cl_sock, rbuf, sizeof(rbuf)-1) ;
    rbuf[nbytes] = '\0' ;
    fprintf(LOG, "[%c] Received: %s\n", id, rbuf) ;
    close(cl_sock) ;
    return(0) ;
}
