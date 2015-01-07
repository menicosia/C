/* secondometer - continuously display Unix time
**
** Jef Poskanzer - 07sep2001
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int
main( int argc, char** argv )
    {
    time_t t, prev_t;

    prev_t = (time_t) 0;
    for (;;)
	{
	t = time( (time_t*) 0 );
	if ( t != prev_t )
	    {
	    (void) printf( "\r%ld  ", (long) t );
	    (void) fflush( stdout );
	    }
	if ( (long) t == 1000000000L || (long) t == 1111111111L )
	    {
	    (void) printf( "" );
	    (void) fflush( stdout );
	    }
	(void) usleep( 200000 );
	prev_t = t;
	}
    }
